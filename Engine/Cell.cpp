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

void Cell::DrawHighlight(Graphics & gfx, Color c) const
{
	gfx.DrawRectStroke(rect, -2, c);
}

void Cell::DrawMark(Graphics & gfx, Color c) const
{
	gfx.DrawCircle( Vec2(rect.GetCenter()), 6.0f, c);
}

RectI Cell::GetRect() const
{
	return rect;
}
