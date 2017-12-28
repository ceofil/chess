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

bool Cell::IsOccupied() const
{
	return !(piece == nullptr);
}

void Cell::SetPiece(Piece * ptr)
{
	piece = ptr;
}

Piece * const Cell::GetPiece() const
{
	return piece;
}

RectI Cell::GetRect() const
{
	return rect;
}

