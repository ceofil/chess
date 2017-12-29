#pragma once
#include "Rect.h"
#include "Graphics.h"
#include "Piece.h"

class Cell
{
public:
	Cell() = default;
	Cell(RectI rect);
	void Draw(Graphics& gfx, Color c) const;

private:
	RectI rect;
};