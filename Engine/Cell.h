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
	void DrawHighlight(Graphics& gfx, Color c) const;
	void DrawMark(Graphics& gfx, Color c) const;
	RectI GetRect() const;
	Vei2 GetLeftTop() const;

private:
	RectI rect;
};