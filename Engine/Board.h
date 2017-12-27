#pragma once
#include "Graphics.h"
#include "Cell.h"
#include "Surface.h"
#include "SpriteEffect.h"
#include "Piece.h"


class Board
{
public:
	Board() = default;
	Board(RectI rect);
	void Draw(Graphics& gfx) const;

private:
	static constexpr int width = 8;
	static constexpr int height = 8;
	Cell cells[width * height];

private:
	Surface sprite = Surface("Sprites\\ChessPiecesArray320x120.bmp");
	const Color clr[2] = { Color(240,217,181),Color(181,136,99) };
};