#include <INIReader.h>
#include <raylib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "simulation.h"
#include "config.h"

int main()
{
	// ####################
	// # READ CONFIG FILE #
	// ####################

	Config config;
	int initOK = config.Initialization();
	if (initOK == 1) { return 1; }
	INIReader reader(config.GetFileName());
	
	// ##################
	// # INICIALIZATION #
	// ##################

	// Constants
	const int WINDOW_WIDTH = reader.GetInteger("window", "width", 1280);
	const int WINDOW_HEIGHT = reader.GetInteger("window", "height", 720);
	const int CELL_SIZE = reader.GetInteger("cell", "size", 5);
	const Color GREY = { reader.GetInteger("cell","edgeColorR",60), reader.GetInteger("cell","edgeColorG",60), reader.GetInteger("cell","edgeColorB",60), 255 };
	const std::string GAME_NAME = "Mikesh's Game of Life";
	const std::string HYPEN = " | ";
	const char* windowTitle = GAME_NAME.c_str();
	
	// Set variables
	int fps = reader.GetInteger("window", "fps", 30);
	fps = (fps < 1) ? 1 : fps;
	fps = (fps > 1000) ? 1000 : fps;

	int edgeWidth = reader.GetInteger("cell", "edgeWidth", 1);
	edgeWidth = (edgeWidth < 0) ? 0 : edgeWidth;
	edgeWidth = (edgeWidth > CELL_SIZE - 1) ? CELL_SIZE - 1 : edgeWidth;
	
	bool randomColors = reader.GetBoolean("cell","randomColors", true);
	bool fullscreen = reader.GetBoolean("window", "fullscreen", false);
	bool state = false;

	// Init Main window
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle);
	if (fullscreen) { ToggleFullscreen(); }
	SetTargetFPS(fps);

	// Create and set up simulation
	Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
	simulation.SetEdges(edgeWidth);
	if (randomColors != simulation.IsRandomColors()) { simulation.ToggleRandomColors(); }

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
			int row = mousePosition.y / CELL_SIZE;
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
		std::string runStatus = simulation.IsRunning() ? "[SPC] Running" : "[SPC] Pause";
		std::string fpsStatus = "[UP/DOWN] Speed: " + std::to_string(fps);
		std::string randomStatus = simulation.IsRandomColors() ? "[C] Colors: ON" : "[C] Colors: OFF";
		std::string edgesStatus = "[LEFT/RIGHT] Edges: " + std::to_string(simulation.GetEdges());
		std::string strTitle = GAME_NAME + HYPEN + runStatus + HYPEN + fpsStatus + HYPEN + randomStatus + HYPEN + edgesStatus + HYPEN + "[ENTER] Clear/Generate canvas | [LMB/RMB] Draw/Clear point";
		windowTitle = strTitle.c_str();
		SetWindowTitle(windowTitle);

		// Drawing the window
		BeginDrawing();
		ClearBackground(GREY);
		simulation.Draw();
		EndDrawing();
	}

	CloseWindow();
}

// Definition of WinMain for Windows subsystem
int WinMain()
{
	return main();
}