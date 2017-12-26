#pragma once
#include "Rect.h"
#include "Graphics.h"

class Cell
{
public:
	Cell() = default;
	Cell(RectI rect);
	void Draw(Graphics& gfx, Color c) const;
	bool IsOccupied() const;
private:
	bool occupied = false;
	RectI rect;
};