#pragma once
#include "Graphics.h"
#include "Cell.h"


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
	const Color clr[2] = { Colors::White,Colors::Black };
};