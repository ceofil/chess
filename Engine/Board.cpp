#include "Board.h"

Board::Board(RectI rect)
{
	const int cellWidth = (rect.GetWidth() + 1) / width;
	const int cellHeight = (rect.GetHeight() + 1) / height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cells[y*width + x] = Cell(
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
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cells[y*width + x].Draw(gfx, clr[(x + y) % 2]);
		}
	}
}
