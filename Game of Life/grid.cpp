#include <raylib.h>
#include "grid.h"

void Grid::Draw()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			// Randomize colors
			if (randomColors)
			{
				int randomValue = 0;
				// live color
				randomValue = GetRandomValue(0, 20);
				tempLive.r = live.r + randomValue;
				randomValue = GetRandomValue(-10, 10);
				tempLive.g = live.g + randomValue;
				randomValue = GetRandomValue(-10, 10);
				tempDead.b = dead.b + randomValue;
				// dead color
				randomValue = GetRandomValue(-10, 10);
				tempDead.r = dead.r + randomValue;
				randomValue = GetRandomValue(-10, 10);
				tempDead.g = dead.g + randomValue;
				randomValue = GetRandomValue(-10, 10);
				tempLive.b = live.b + randomValue;
			}

			// Draw
			Color color = cells[row][column] ? tempLive : tempDead;
			DrawRectangle(column * cellSize, row * cellSize, cellSize - edgesWidth, cellSize - edgesWidth, color);
		}
	}
}

void Grid::SetValue(int row, int column, int value)
{
	if (IsWithinBounds(row, column))
	{
		cells[row][column] = value;
	}
}

int Grid::GetValue(int row, int column)
{
	if (IsWithinBounds(row,column))
	{
		return cells[row][column];
	}
}

int Grid::GetRows()
{
	return rows;
}

int Grid::GetColumns()
{
	return columns;
}

void Grid::FillRandom()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			int randomValue = GetRandomValue(0, 4);
			cells[row][column] = (randomValue == 4) ? 1 : 0;
		}
	}
}

void Grid::Clear()
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			cells[row][column] = 0;
		}
	}
}

bool Grid::IsClear()
{
	int sum = 0;

	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			sum += cells[row][column];
		}
	}

	return (sum == 0) ? true : false;
}

void Grid::ToggleCell(int row, int column, bool state)
{
	if (IsWithinBounds(row, column))
	{
		cells[row][column] = (state) ? 1 : 0;
	}
}

void Grid::ToggleRandomColors()
{
	randomColors = !randomColors;
}

bool Grid::IsRandomColors()
{
	return randomColors;
}

void Grid::SetEdges(int edgeWidth)
{
	edgesWidth = edgeWidth;
}

int Grid::GetEdges()
{
	return edgesWidth;
}

bool Grid::IsWithinBounds(int row, int column)
{
	return (row >= 0 && row < rows && column >= 0 && column < columns) ? true : false;
}
