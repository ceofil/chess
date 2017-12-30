#include "Cell.h"

Cell::Cell(RectI rect)
	:
	rect(rect)
{
}

void Cell::Draw(Graphics & gfx, Color c) const
{
	gfx.DrawRect(rect, c);
}

RectI Cell::GetRect() const
{
	return rect;
}
