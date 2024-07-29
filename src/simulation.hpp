#pragma once
#include "grid.hpp"
#include <utility>
#include <vector>

using namespace std;

class Simulation
{
public:
  Simulation (int width, int height, int cellSize)
      : grid (width, height, cellSize), tempGrid (width, height, cellSize),
        run (false) {};
  // Draw the grid
  void Draw ();
  // Set the value of the cell
  void SetCellValue (int row, int column, int value);
  // Count how many live neighbours the cell have
  int CountLiveNeighbours (int row, int column);
  // Iterate next generation
  void Update ();
  // Is simulation running?
  bool IsRunning ();
  // Is the grid is full of dead cells?
  bool IsClear ();
  // Start the simulation
  void Start ();
  // Stop the simulation
  void Stop ();
  // Clear the grid
  void ClearGrid ();
  // Fill grid randomly with live and dead cells
  void CreateRandomState ();
  // Change the status of the cell. State true => live / false => dead
  void ToggleCell (int row, int column, bool state);
  // Turn on/off random colors
  void ToggleRandomColors ();
  // Is RandomColor feature turn on?
  bool IsRandomColors ();
  // Set the width of the edges of the cells
  void SetEdges (int edge);
  // Return back the current width of the edges of the cells
  int GetEdges ();
  // Set color and alpha of the dead cell
  void SetColor (bool isLiveColor, int red, int green, int blue, int alpha);
  // Set the range of color change allowed for RandomColors feature
  void SetRandomSize (int value);
  // Reset Generation to zero
  void ResetGeneration ();
  // AddGaneration by 1
  void AddGeneration ();
  // Get number of current generation
  unsigned long GetGeneration ();

private:
  // Main grid for simulation
  Grid grid;
  // Temporary grid for calculation of next generation
  Grid tempGrid;
  // Simulation is running
  bool run{};
  // Generation counter
  unsigned long generation{};
};
