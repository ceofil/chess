#include "Piece.h"


Piece::Piece(RectI whiteRect, RectI blackRect, int side)
{
	rect[0] = whiteRect;
	rect[1] = blackRect;
	this->side = side;
}

void Piece::Draw(Vei2 pos, const Surface& surface, Graphics & gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, rect[side], surface, SpriteEffect::Chroma{ Colors::Magenta });
}

King::King(int side)
	:
	Piece(RectI(size, 2 * size, 0, size), RectI(size, 2 * size, size, 2 * size), side)
{
}

Queen::Queen(int side)
	:
	Piece(RectI(0, size, 0, size), RectI(0, size, size, 2 * size), side)
{
}

Rook::Rook(int side)
	:
	Piece(RectI(2 * size, 3 * size, 0, size), RectI(2 * size, 3 * size, size, 2 * size), side)
{
}

Knight::Knight(int side)
	:
	Piece(RectI(3 * size, 4 * size, 0, size), RectI(3 * size, 4 * size, size, 2 * size), side)
{
}

Bishop::Bishop(int side)
	:
	Piece(RectI(4 * size, 5 * size, 0, size), RectI(4 * size, 5 * size, size, 2 * size), side)
{
}

Pawn::Pawn(int side)
	:
	Piece(RectI(5 * size, 6 * size, 0, size), RectI(5 * size, 6 * size, size, 2 * size), side)
{
}
