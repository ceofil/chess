#pragma once
#include "Graphics.h"
#include "Cell.h"
#include "Surface.h"
#include "SpriteEffect.h"
#include "Piece.h"
#include <vector>
#include "PieceManager.h"
#include "Mouse.h"

class Board
{
public:
	Board() = default;
	Board(RectI rect);
	void Draw(Graphics& gfx) const;
	void HandleMousePressed(Vei2 screenPos);

private:
	RectI rect;
	int cellSize;
	Cell cells[64];
	const Cell& CellAt(int x, int y) const;
	Cell& CellAt(int x, int y);
	Vei2 pieceScreenPos(int x, int y) const;

private:
	Surface sprite = Surface("Sprites\\ChessPiecesArray320x120.bmp");
	const Color clr[2] = { Color(240,217,181),Color(181,136,99) };

private:
	PieceManager table;
	void InitializePieces();

private:
	enum class GameState
	{
		Waiting,
		PieceSelected
	};
	GameState state = GameState::Waiting;
	Vei2 selectedPiece = { -1,-1 };
};