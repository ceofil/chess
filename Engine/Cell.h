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
	bool IsOccupied() const;
	void SetPiece(Piece* ptr);
	Piece* const GetPiece() const;
	RectI GetRect() const;

private:
	RectI rect;

private:
	Piece* piece = nullptr;
};