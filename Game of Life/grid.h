#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
			Grid(int width, int height, int cellSize)
				: rows(height / cellSize), columns(width / cellSize), cellSize(cellSize), cells(rows, std::vector<int>(columns, 0)), randomColors(true), edgesWidth(1) {};
	void	Draw();
	void	SetValue(int row, int column, int value);
	int		GetValue(int row, int column);
	int		GetRows();
	int		GetColumns();
	void	FillRandom();
	void	Clear();
	bool	IsClear();
	void	ToggleCell(int row, int column, bool state);
	void	ToggleRandomColors();
	bool	IsRandomColors();
	void	SetEdges(int edge);
	int		GetEdges();

private:
	int								rows;
	int								columns;
	int								cellSize;
	std::vector<std::vector<int>>	cells;
	Color							live		= { 0, 170, 174, 255 };
	Color							tempLive	= live;
	Color							dead		= { 136, 104, 79, 100 };
	Color							tempDead	= dead;
	bool							randomColors;
	int								edgesWidth;
	bool							IsWithinBounds(int row, int column);
};