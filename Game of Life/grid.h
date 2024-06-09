#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid(int width, int height, int cellSize)
		: rows(height / cellSize), columns(width / cellSize), cellSize(cellSize), cells(rows, std::vector<int>(columns, 0)), randomColors(true), edgesWidth(1) {};
	// Draw complete grid
	void Draw();
	// Set the value of the cell
	void SetValue(int row, int column, int value);
	// Get the value of the cell
	int GetValue(int row, int column);
	// Return number of rows
	int GetRows();
	// Return number of columns
	int GetColumns();
	// Fill grid randomly with live and dead cells
	void FillRandom();
	// Clear the grid
	void Clear();
	// Is the grid is full of dead cells?
	bool IsClear();
	// Change the status of the cell. State true => live / false => dead
	void ToggleCell(int row, int column, bool state);
	// Turn on/off random colors
	void ToggleRandomColors();
	// Is RandomColor feature turn on?
	bool IsRandomColors();
	// Set the width of the edges of the cells
	void SetEdges(int width);
	// Return back the current width of the edges of the cells
	int GetEdges();
	// Set color and alpha of the live cell
	void SetColorLive(int red, int green, int blue, int alpha);
	// Set color and alpha of the dead cell
	void SetColorDead(int red, int green, int blue, int alpha);
	// Set the range of color change allowed for RandomColors feature 
	void SetRandomSize(int value);

private:
	// Number of the rows of the grid
	int rows{};
	// Number of the columns of the grid
	int columns{};
	// Size of the cell
	int	cellSize{};
	// Vector of pair of the cells in grid
	std::vector<std::vector<int>> cells{};
	// Color of the live cell
	Color live{};
	// Temporary color of the live cell (used with randomColor feature)
	Color tempLive{};
	// Color of the dead cell
	Color dead{};
	// Temporary color of the dead cell (used with randomColor feature)
	Color tempDead{};
	// Width of the range for randomColor feature (+/-)
	int randomSize{};
	// Cell edge width
	int	edgesWidth{};
	// Turn on/off randomColors feature
	bool randomColors{};
	// Is the row and column within the bound of the grid?
	bool IsWithinBounds(int row, int column);
	// Adjust the color and check if it is in the range of 0 to 255
	int AdjustColorComponent(int colorComponent, int randomSize);
	// Set the color to Color component
	Color SetColor(int red, int green, int blue, int alpha);
};