#include "Piece.h"


Piece::Piece(PieceColor clr, PieceType type, RectI whiteRect, RectI blackRect)
	:
	clr(clr),
	type(type)
{
	rect[(int)PieceColor::White] = whiteRect;
	rect[(int)PieceColor::Black] = blackRect;
}

void Piece::Draw(Vei2 pos, const Surface& surface, Graphics & gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, rect[(int)clr], surface, SpriteEffect::Chroma{ Colors::Magenta });
}

PieceType Piece::GetType() const
{
	return type;
}

PieceColor Piece::GetColor() const
{
	return clr;
}

King::King(PieceColor clr)
	:
	Piece(clr, PieceType::King, RectI(size, 2 * size, 0, size), RectI(size, 2 * size, size, 2 * size))
{
}

Queen::Queen(PieceColor clr)
	:
	Piece(clr, PieceType::Queen, RectI(0, size, 0, size), RectI(0, size, size, 2 * size))
{
}

Rook::Rook(PieceColor clr)
	:
	Piece(clr, PieceType::Rook, RectI(2 * size, 3 * size, 0, size), RectI(2 * size, 3 * size, size, 2 * size))
{
}

Knight::Knight(PieceColor clr)
	:
	Piece(clr, PieceType::Knight, RectI(3 * size, 4 * size, 0, size), RectI(3 * size, 4 * size, size, 2 * size))
{
}

Bishop::Bishop(PieceColor clr)
	:
	Piece(clr, PieceType::Bishop, RectI(4 * size, 5 * size, 0, size), RectI(4 * size, 5 * size, size, 2 * size))
{
}

Pawn::Pawn(PieceColor clr)
	:
	Piece(clr, PieceType::Pawn, RectI(5 * size, 6 * size, 0, size), RectI(5 * size, 6 * size, size, 2 * size))
{
}
