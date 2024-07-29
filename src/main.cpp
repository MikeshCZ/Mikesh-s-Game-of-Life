#include "intro.hpp"
#include "settings.hpp"
#include "simulation.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <raylib.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "../ext/raygui-4.0/src/raygui.h"

using namespace std;

int
main ()
{
  // ####################
  // # READ CONFIG FILE #
  // ####################

  // Read the configuration file with settings
  // Set up default value
  Settings settings
      = { 1280, 720, 60,  false, true, true, 5,   1,  true, 10, 0,
          170,  170, 255, 140,   100,  80,   130, 60, 60,   60 };

  // Startup will chekc if the settings file exist, if not create new one with
  // default values
  settings.Startup ();

  // ##################
  // # INICIALIZATION #
  // ##################

  // ---------
  // Constants
  // ---------

  const int WINDOW_WIDTH = settings.width;    // Main window width
  const int WINDOW_HEIGHT = settings.height;  // Main window height
  const int GRID_WIDTH = WINDOW_WIDTH;        // Grid width
  const int GRID_HEIGHT = WINDOW_HEIGHT - 30; // Grid height
  const int CELL_SIZE = settings.size;        // One cell size
  const Color EDGE = { // Read edge color from the config
                       static_cast<unsigned char> (settings.edgeColorR),
                       static_cast<unsigned char> (settings.edgeColorG),
                       static_cast<unsigned char> (settings.edgeColorB)
  };
  const string GAME_NAME = "Mikesh's Game of Life"; // Game name in the title
  const string HYPEN = " | "; // Hypen for the text in the top bar
  const char *windowTitle = GAME_NAME.c_str (); // Window title
  const char *helpText =                        // Text for the F1 Help window
      "[F1] - Show/Close this help\n\n"
      "[Left Click] - Add cell state (alive).\n"
      "[Right Click] - Remove cell state (dead).\n\n"
      "[Space] - Start/stop the simulation.\n"
      "[ENTER] - Clear / Reset the board.\n\n"
      "[Key up] - Increase the simulation speed.\n"
      "[Key down] - Decrease the simulation speed.\n"
      "[Key left] - Increase cell edges.\n"
      "[Key right] - Decrease cell edges.\n\n"
      "[S] - Only one generation (when game is paused).\n"
      "[F] - Toggle fullscreen ON/OFF.\n"
      "[C] - Turn on/off random colors.\n"
      "[M] - Music on/off.\n\n"
      "[F10] - Exit the game.";

  // -------------
  // Set variables
  // -------------

  int fps = settings.fps; // Target FPS of the app
  fps = clamp (fps, 1, 999);

  int edgeWidth = settings.edgeWidth; // Width of the cell edges
  edgeWidth = clamp (edgeWidth, 0, CELL_SIZE - 1);

  bool randomColors = settings.randomColors; // Random colors feature
  bool fullscreen = settings.fullscreen;     // Fullscreen
  bool state{};                              // State of the cell (live/dead)
  bool IsMenuActive = false;                 // Show help window
  Vector2
      mousePosition{};   // Reading actual position of the mouse in the window
  Vector4 menuWindow = { // Menu window parameter x, y, width, height
                         static_cast<float> (WINDOW_WIDTH / 2 - 150),
                         static_cast<float> (WINDOW_HEIGHT / 2 - 200),
                         static_cast<float> (300), static_cast<float> (400)
  };
  Vector2 panOffset{};   // Ofset of the mouse when dragging the main window
  bool dragMenu = false; // Dragging the menu window
  bool oneStep = false;  // oneStep mode

  // ----------------
  // Init Main window
  // ----------------

  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle);
  if (fullscreen)
    {
      ToggleFullscreen ();
    }
  SetTargetFPS (fps);
  SetExitKey (KEY_F10);

  Intro intro{};                       // Raylib Intro screen
  bool playIntro = settings.playIntro; // Play raylib intro

  InitAudioDevice ();              // Inicialization of background music
  bool playMusic = settings.music; // Play background music

  Music music = LoadMusicStream ("audio/music.ogg"); // Music stream
  SetMusicVolume (music, 1.0f);                      // Set volume
  PlayMusicStream (music);                           // Play music stream

  // ----------------------------
  // Create and set up simulation
  // ----------------------------

  Simulation simulation (GRID_WIDTH, GRID_HEIGHT,
                         CELL_SIZE); // Main simulation class
  simulation.SetEdges (edgeWidth);   // Set up edge width

  // Set up colors from INI file
  simulation.SetColor (true, settings.liveColorR, settings.liveColorG,
                       settings.liveColorB, settings.liveColorA);

  simulation.SetColor (false, settings.deadColorR, settings.deadColorG,
                       settings.deadColorB, settings.deadColorA);

  // randomColors from INI file
  if (randomColors != simulation.IsRandomColors ())
    {
      simulation.ToggleRandomColors ();
    }
  simulation.SetRandomSize (settings.randomSize);

  // -------------
  // Play Intro
  // -------------

  if (playIntro)
    {
      SetTargetFPS (60); // Set FPS to 60 to have same lenght of the video

      while (WindowShouldClose () == false && playIntro)
        {
          if (playMusic)
            {
              UpdateMusicStream (music);
            }

          if (!intro.IsIntroFininsh ())
            {
              BeginDrawing ();
              ClearBackground (RAYWHITE);
              intro.UpdateLogoScreen ();
              intro.DrawLogoScreen ();
              EndDrawing ();
            }
          else // Intro is finish
            {
              SetTargetFPS (fps); // set back the FPS to config value
              break;
            }
        }
    }

  // #############
  // # MAIN LOOP #
  // #############

  while (WindowShouldClose () == false)
    {
      if (playMusic)
        {
          UpdateMusicStream (music);
        }

      // -----------------
      // 1. Event handling
      // -----------------

      mousePosition = GetMousePosition ();

      //  Mouse click when menu is not active
      if ((IsMouseButtonDown (MOUSE_BUTTON_LEFT)
           || IsMouseButtonDown (MOUSE_BUTTON_RIGHT))
          && !IsMenuActive)
        {
          if (IsMouseButtonDown (MOUSE_BUTTON_LEFT))
            {
              state = true;
            }
          else if (IsMouseButtonDown (MOUSE_BUTTON_RIGHT))
            {
              state = false;
            }

          int row = (mousePosition.y - 30)
                    / CELL_SIZE; // minus top bar width 30 px
          int column = mousePosition.x / CELL_SIZE;
          simulation.ToggleCell (row, column, state);
        }
      // Left mouse click when menu is open
      else if (IsMouseButtonDown (MOUSE_BUTTON_LEFT) && !dragMenu
               && IsMenuActive)
        {
          if (CheckCollisionPointRec (
                  mousePosition,
                  { menuWindow.x, menuWindow.y, menuWindow.z - 20, 20 }))
            {
              dragMenu = true;
              panOffset = { (mousePosition.x - menuWindow.x),
                            (mousePosition.y - menuWindow.y) };
            }
        }
      // drag menu window
      if (dragMenu)
        {
          menuWindow.x = (mousePosition.x - panOffset.x);
          menuWindow.y = (mousePosition.y - panOffset.y);

          if (IsMouseButtonReleased (MOUSE_BUTTON_LEFT))
            dragMenu = false;
        }

      // Start/Stop with SPACE KEY
      if (IsKeyPressed (KEY_SPACE))
        {
          if (simulation.IsRunning ())
            {
              simulation.Stop ();
            }
          else
            {
              simulation.Start ();
            }
        }
      // Speed up
      else if (IsKeyDown (KEY_UP))
        {
          fps += 1;
          fps = (fps > 999) ? 999 : fps;
          SetTargetFPS (fps);
        }
      // Speed down
      else if (IsKeyDown (KEY_DOWN))
        {
          fps -= 1;
          fps = (fps < 1) ? 1 : fps;
          SetTargetFPS (fps);
        }
      // Edges up
      else if (IsKeyPressed (KEY_RIGHT))
        {
          edgeWidth = simulation.GetEdges ();
          edgeWidth += 1;
          edgeWidth = (edgeWidth > CELL_SIZE - 1) ? CELL_SIZE - 1 : edgeWidth;
          simulation.SetEdges (edgeWidth);
        }
      // Edges down
      else if (IsKeyPressed (KEY_LEFT))
        {
          edgeWidth = simulation.GetEdges ();
          edgeWidth -= 1;
          edgeWidth = (edgeWidth < 0) ? 0 : edgeWidth;
          simulation.SetEdges (edgeWidth);
        }
      // Clear/Create Grid
      else if (IsKeyPressed (KEY_ENTER))
        {
          if (simulation.IsClear ())
            {
              simulation.CreateRandomState ();
              simulation.ResetGeneration ();
              simulation.Start ();
            }
          else
            {
              if (simulation.IsRunning ())
                {
                  simulation.Stop ();
                  simulation.CreateRandomState ();
                  simulation.ResetGeneration ();
                  simulation.Start ();
                }
              else
                {
                  simulation.ClearGrid ();
                  simulation.ResetGeneration ();
                }
            }
        }
      // Toogle random color effect
      else if (IsKeyPressed (KEY_C))
        {
          simulation.ToggleRandomColors ();
        }
      // Fullscreen toggle
      else if (IsKeyPressed (KEY_F))
        {
          ToggleFullscreen ();
        }
      // Open / close menu
      else if (IsKeyPressed (KEY_F1)
               || (IsMenuActive && IsKeyPressed (KEY_ESCAPE)))
        {
          IsMenuActive = !IsMenuActive;
        }
      // One step
      else if (IsKeyPressed (KEY_S) && !simulation.IsRunning () && !oneStep)
        {
          oneStep = true;
          simulation.Start ();
        }
      // Play/Pause music
      else if (IsKeyPressed (KEY_M))
        {
          playMusic ? PauseMusicStream (music) : ResumeMusicStream (music);
          playMusic = !playMusic;
        }

      // -----------------
      // 2. Updating state
      // -----------------

      simulation.Update ();
      if (simulation.IsClear ())
        {
          simulation.Stop ();
        }

      // ----------
      // 3. Drawing
      // ----------

      // Update top bar title
      string runStatus = simulation.IsRunning () ? "Running" : "Pause";
      string fpsStatus = "Target FPS: " + to_string (fps);

      string strInfo
          = GAME_NAME + HYPEN + runStatus + HYPEN + fpsStatus + HYPEN
            + "Press F1 to open MENU" + HYPEN
            + "Generation: " + to_string (simulation.GetGeneration ());
      const char *info = strInfo.c_str ();

      // Drawing the window
      BeginDrawing ();
      ClearBackground (EDGE);                        // Clear the background
      DrawRectangle (0, 0, WINDOW_WIDTH, 30, BLACK); // Draw top bar
      DrawText (info, 5, 5, 20, WHITE);              // Write top bar text
      DrawFPS (WINDOW_WIDTH - 90, 5); // Write FPS to right corner

      simulation.Draw (); // Draw new grid

      if (IsMenuActive) // F1 Menu open
        {
          IsMenuActive = !GuiWindowBox (
              { menuWindow.x, menuWindow.y, menuWindow.z, menuWindow.w },
              "#198#Menu");
          DrawText (helpText, menuWindow.x + 10, menuWindow.y + 30, 10,
                    DARKGRAY);
        }
      EndDrawing ();

      if (oneStep)
        {
          oneStep = false;
          simulation.Stop ();
        }
    }
  UnloadMusicStream (music);
  CloseAudioDevice ();
  CloseWindow ();
}