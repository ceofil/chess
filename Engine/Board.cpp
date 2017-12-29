#include "Board.h"

Board::Board(RectI rect)
{
	const int cellWidth = (rect.GetWidth() + 1) / 8;
	const int cellHeight = (rect.GetHeight() + 1) / 8;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			CellAt(x, y) = Cell(
				RectI(
					rect.left + x * cellWidth,
					rect.left + (x + 1) * cellWidth,
					rect.top + y * cellHeight,
					rect.top + (y + 1) * cellHeight
				));
		}
	}
}

void Board::Draw(Graphics & gfx) const
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			CellAt(x, y).Draw(gfx, clr[(x + y) % 2]);
		}
	}
}

const Cell & Board::CellAt(int x, int y) const
{
	return cells[y * 8 + x];
}

Cell & Board::CellAt(int x, int y)
{
	return cells[y * 8 + x];
}

