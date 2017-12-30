#pragma once
#include "Graphics.h"
#include "Cell.h"
#include "Surface.h"
#include "SpriteEffect.h"
#include "Piece.h"
#include <vector>
#include "PieceManager.h"

class Board
{
public:
	Board() = default;
	Board(RectI rect);
	void Draw(Graphics& gfx) const;

private:
	Cell cells[64];
	const Cell& CellAt(int x, int y) const;
	Cell& CellAt(int x, int y);

private:
	Surface sprite = Surface("Sprites\\ChessPiecesArray320x120.bmp");
	const Color clr[2] = { Color(240,217,181),Color(181,136,99) };

private:
	PieceManager table;
};