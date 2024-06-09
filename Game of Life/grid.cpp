#include <raylib.h>
#include <algorithm>
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
				// live color
				tempLive.r = AdjustColorComponent(live.r, randomSize);
				tempLive.g = AdjustColorComponent(live.g, randomSize);
				tempLive.b = AdjustColorComponent(live.b, randomSize);
				tempLive.a = AdjustColorComponent(live.a, randomSize);

				// dead color
				tempDead.r = AdjustColorComponent(dead.r, randomSize);
				tempDead.g = AdjustColorComponent(dead.g, randomSize);
				tempDead.b = AdjustColorComponent(dead.b, randomSize);
				tempDead.a = AdjustColorComponent(dead.a, randomSize);
			}

			// Draw
			Color color = cells[row][column] ? tempLive : tempDead;
			DrawRectangle(column * cellSize, row * cellSize + 30, cellSize - edgesWidth, cellSize - edgesWidth, color);
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
	else
	{
		return 0;
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

void Grid::SetEdges(int width)
{
	edgesWidth = width;
}

int Grid::GetEdges()
{
	return edgesWidth;
}

void Grid::SetColorLive(int red, int green, int blue, int alpha)
{
	live = SetColor(red, green, blue, alpha);
	tempLive = live;
}

void Grid::SetColorDead(int red, int green, int blue, int alpha)
{
	dead = SetColor(red, green, blue, alpha);
	tempDead = dead;
}

void Grid::SetRandomSize(int value)
{
	randomSize = value;
}

bool Grid::IsWithinBounds(int row, int column)
{
	return (row >= 0 && row < rows && column >= 0 && column < columns) ? true : false;
}

int Grid::AdjustColorComponent(int colorComponent, int randomSize)
{
	randomSize = std::clamp(randomSize, 0, 127);
	int randomValue = GetRandomValue(-randomSize, randomSize);
	int adjustedValue = colorComponent + randomValue;
	return std::clamp(adjustedValue, 0, 255);
}

Color Grid::SetColor(int red, int green, int blue, int alpha)
{
	Color color;
	color.r = std::clamp(red, 0, 255);
	color.g = std::clamp(green, 0, 255);
	color.b = std::clamp(blue, 0, 255);
	color.a = std::clamp(alpha, 0, 255);

	return color;
}