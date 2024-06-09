#include <INIReader.h>
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "simulation.h"
#include "config.h"

int main()
{
	// ####################
	// # READ CONFIG FILE #
	// ####################

	Config config;
	int initOK = config.Initialization();

	// If reading of the config fail return 1
	if (initOK == 1) { return 1; }
	
	INIReader reader(config.GetFileName());
	
	// ##################
	// # INICIALIZATION #
	// ##################

	// ---------
	// Constants
	// ---------

	const int WINDOW_WIDTH = reader.GetInteger("window", "width", 1280);
	const int WINDOW_HEIGHT = reader.GetInteger("window", "height", 720);
	const int GRID_WIDTH = WINDOW_WIDTH;
	const int GRID_HEIGHT = WINDOW_HEIGHT - 30;
	const int CELL_SIZE = reader.GetInteger("cell", "size", 5);
	const Color EDGE = { reader.GetInteger("color","edgeColorR",60), reader.GetInteger("color","edgeColorG",60), reader.GetInteger("color","edgeColorB",60), 255 };
	const std::string GAME_NAME = "Mikesh's Game of Life";
	const std::string HYPEN = " | ";
	const char* windowTitle = GAME_NAME.c_str();
	
	// Text for the F1 Help window
	const char* helpText = 
		"F1							Show/Close this help\n\n"
		"Left Click			Add cell state (alive).\n"
		"Right Click			Remove cell state (dead).\n\n"
		"Space					Start/stop the simulation.\n"
		"ENTER				Clear / Reset the board.\n\n"
		"Key up				Increase the simulation speed.\n"
		"Key down			Decrease the simulation speed.\n"
		"Key left			Increase cell edges.\n"
		"Key right			Decrease cell edges.\n\n"
		"F								Toggle fullscreen ON/OFF.\n"
		"C								Turn on/off random colors.\n\n"
		"F10						Exit the game.";
	
	// -------------
	// Set variables
	// -------------
	
	// Target FPS of the app
	int fps = reader.GetInteger("window", "fps", 30);
	fps = std::clamp(fps, 1, 240);

	// Width of the cell edges
	int edgeWidth = reader.GetInteger("cell", "edgeWidth", 1);
	edgeWidth = std::clamp(edgeWidth, 0, CELL_SIZE - 1);
	
	// Random colors feature 
	bool randomColors = reader.GetBoolean("cell","randomColors", true);

	// Fullscreen
	bool fullscreen = reader.GetBoolean("window", "fullscreen", false);
	
	// State of the cell (live/dead)
	bool state;
	
	// Show help window
	bool showHelp = false;

	// Main Help widnow as rectangle
	Rectangle helpWindow = { WINDOW_WIDTH/2 - 400/2, WINDOW_HEIGHT/2 - 280/2, 400, 280 };

	// ----------------
	// Init Main window
	// ----------------

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle);
	if (fullscreen) { ToggleFullscreen(); }
	SetTargetFPS(fps);
	SetExitKey(KEY_F10);

	// ----------------------------
	// Create and set up simulation
	// ----------------------------

	// Main simulation class
	Simulation simulation(GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);
	
	// Set up edge width
	simulation.SetEdges(edgeWidth);
	
	// Set up colors from INI file
	simulation.SetColor(true, reader.GetInteger("color", "liveColorR", 0), reader.GetInteger("color", "liveColorG", 170), reader.GetInteger("color", "liveColorB", 170), reader.GetInteger("color", "liveColorA", 255));
	simulation.SetColor(false, reader.GetInteger("color", "deadColorR", 140), reader.GetInteger("color", "deadColorG", 100), reader.GetInteger("color", "deadColorB", 80), reader.GetInteger("color", "deadColorA", 130));
	
	// randomColors from INI file
	if (randomColors != simulation.IsRandomColors()) { simulation.ToggleRandomColors(); }
	simulation.SetRandomSize(reader.GetInteger("cell", "randomSize", 10));
	
	// #############
	// # MAIN LOOP #
	// #############

	while (WindowShouldClose() == false)
	{
		// -----------------
		// 1. Event handling
		// -----------------

		//  Mouse click
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				state = true;
			}
			else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				state = false;
			}
			
			Vector2 mousePosition = GetMousePosition();
			int row = (mousePosition.y - 30) / CELL_SIZE;
			int column = mousePosition.x / CELL_SIZE;
			simulation.ToggleCell(row, column, state);
		}
		// Start/Stop with SPACE KEY
		if (IsKeyPressed(KEY_SPACE))
		{
			if (simulation.IsRunning())
			{
				simulation.Stop();
			}
			else
			{
				simulation.Start();
			}
		}
		// Speed up
		else if (IsKeyDown(KEY_UP))
		{
			fps += 1;
			fps = (fps > 1000) ? 1000 : fps;
			SetTargetFPS(fps);
		}
		// Speed down
		else if (IsKeyDown(KEY_DOWN))
		{
			fps -= 1;
			fps = (fps < 1) ? 1 : fps;
			SetTargetFPS(fps);
		}
		// Edges up
		else if (IsKeyPressed(KEY_RIGHT))
		{
			edgeWidth = simulation.GetEdges();
			edgeWidth += 1;
			edgeWidth = (edgeWidth > CELL_SIZE - 1) ? CELL_SIZE - 1 : edgeWidth;
			simulation.SetEdges(edgeWidth);
		}
		// Edges down
		else if (IsKeyPressed(KEY_LEFT))
		{
			edgeWidth = simulation.GetEdges();
			edgeWidth -= 1;
			edgeWidth = (edgeWidth < 0) ? 0 : edgeWidth;
			simulation.SetEdges(edgeWidth);
		}
		// Clear/Create Grid
		else if (IsKeyPressed(KEY_ENTER))
		{
			if (simulation.IsClear())
			{
				simulation.CreateRandomState();
				simulation.Start();
			}
			else
			{
				if (simulation.IsRunning())
				{
					simulation.Stop();
					simulation.CreateRandomState();
					simulation.Start();

				}
				else
				{
					simulation.ClearGrid();
				}
			}
		}
		// Toogle random color effect
		else if (IsKeyPressed(KEY_C))
		{
			simulation.ToggleRandomColors();
		}
		// Fullscreen toggle
		else if (IsKeyPressed(KEY_F))
		{
			ToggleFullscreen();
		}
		else if (IsKeyPressed(KEY_F1) || (showHelp && IsKeyPressed(KEY_ESCAPE)))
		{
			showHelp = !showHelp;
		}
		 
		// -----------------
		// 2. Updating state
		// -----------------

		simulation.Update();
		if (simulation.IsClear())
		{
			simulation.Stop();
		}

		// ----------
		// 3. Drawing
		// ----------
		
		// Update windows title
		std::string runStatus = simulation.IsRunning() ? "Running" : "Pause";
		std::string fpsStatus = "Target FPS: " + std::to_string(fps);
		std::string strInfo = GAME_NAME + HYPEN + runStatus + HYPEN + fpsStatus + HYPEN + "Press F1 for help";
		const char* info = strInfo.c_str();

		// Drawing the window
		BeginDrawing();
			ClearBackground(EDGE);
			DrawRectangle(0, 0, WINDOW_WIDTH, 30, BLACK);
			DrawText(info, 5, 5, 20, WHITE);
			DrawFPS(WINDOW_WIDTH - 90, 5);
			simulation.Draw();
			if (showHelp)
			{
				DrawRectangleRec(helpWindow, Fade(SKYBLUE, 0.5f));
				DrawRectangleLinesEx(helpWindow, 3, BLUE);
				DrawText(helpText, helpWindow.x + 10, helpWindow.y + 10, 16, DARKGRAY);
			}
		EndDrawing();
	}
	CloseWindow();
}

// Definition of WinMain for Windows subsystem
int WinMain()
{
	return main();
}