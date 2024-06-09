#pragma once
#include "grid.h"

class Simulation
{
public:
			Simulation(int width, int height, int cellSize)
				: grid(width, height, cellSize), tempGrid(width, height, cellSize), run(false) {};
	void	Draw();
	void	SetCellValue(int row, int column, int value);
	int		CountLiveNeighbours(int row, int column);
	void	Update();
	bool	IsRunning();
	bool	IsClear();
	void	Start();
	void	Stop();
	void	ClearGrid();
	void	CreateRandomState();
	void	ToggleCell(int row, int column, bool state);
	void	ToggleRandomColors();
	bool	IsRandomColors();
	void	SetEdges(int edge);
	int		GetEdges();

private:
	Grid	grid;
	Grid	tempGrid;
	bool	run;
};

