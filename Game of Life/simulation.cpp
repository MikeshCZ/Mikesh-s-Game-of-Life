#include <vector>
#include <utility>
#include "simulation.h"


void Simulation::Draw()
{
	grid.Draw();
}

void Simulation::SetCellValue(int row, int column, int value)
{
	grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbours(int row, int column)
{
	int liveNeighbours = 0;
	std::vector<std::pair<int, int>> neighbourOffsets =
	{
		{-1, 0}, // Directly above
		{1, 0},  // Directly below
		{0, -1}, // To the left
		{0, 1},  // To the right
		{-1, -1},// Diagonal upper left
		{-1, 1}, // Diagonal upper right
		{1, -1}, // Diagonal lower left
		{1, 1}   // Diagonal lower right
	};

	for (const auto& offset : neighbourOffsets)
	{
		int neighbourRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
		int neighbourColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
		liveNeighbours += grid.GetValue(neighbourRow, neighbourColumn);
	}

	return liveNeighbours;
}

void Simulation::Update()
{
	if (IsRunning())
	{
		for (int row = 0; row < grid.GetRows(); row++)
		{
			for (int column = 0; column < grid.GetColumns(); column++)
			{
				int liveNeighbours = CountLiveNeighbours(row, column);
				int cellValue = grid.GetValue(row, column);

				if (cellValue == 1)
				{
					if (liveNeighbours > 3 || liveNeighbours < 2)
					{
						tempGrid.SetValue(row, column, 0);
					}
					else
					{
						tempGrid.SetValue(row, column, 1);
					}
				}
				else
				{
					if (liveNeighbours == 3)
					{
						tempGrid.SetValue(row, column, 1);
					}
					else
					{
						tempGrid.SetValue(row, column, 0);
					}
				}
			}
		}
		grid = tempGrid;
		AddGeneration();
	}
}

bool Simulation::IsRunning()
{
	return run;
}

bool Simulation::IsClear()
{
	return grid.IsClear();
}

void Simulation::Start()
{
	run = true;
}

void Simulation::Stop()
{
	run = false;
}

void Simulation::ClearGrid()
{
	if (!IsRunning())
	{
		grid.Clear();
	}
}

void Simulation::CreateRandomState()
{
	if (!IsRunning())
	{
		grid.FillRandom();
	}
}

void Simulation::ToggleCell(int row, int column, bool state)
{
		grid.ToggleCell(row, column, state);
}

void Simulation::ToggleRandomColors()
{
	grid.ToggleRandomColors();
	tempGrid.ToggleRandomColors();
}

bool Simulation::IsRandomColors()
{
	return grid.IsRandomColors();
}

void Simulation::SetEdges(int edge)
{
	grid.SetEdges(edge);
	tempGrid.SetEdges(edge);
}

int Simulation::GetEdges()
{
	return grid.GetEdges();
}

void Simulation::SetColor(bool isLiveColor, int red, int green, int blue, int alpha)
{
	if (isLiveColor)
	{
		grid.SetColorLive(red, green, blue, alpha);
		tempGrid.SetColorLive(red, green, blue, alpha);
	}
	else
	{
		grid.SetColorDead(red, green, blue, alpha);
		tempGrid.SetColorDead(red, green, blue, alpha);
	}
}

void Simulation::SetRandomSize(int value)
{
	grid.SetRandomSize(value);
	tempGrid.SetRandomSize(value);
}

void Simulation::ResetGeneration()
{
	generation = 0;
}

void Simulation::AddGeneration()
{
	generation++;
}

unsigned long Simulation::GetGeneration()
{
	return generation;
}
