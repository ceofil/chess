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
	bool IsCheckMate() const;
	void Reset();

private:
	RectI rect;
	int cellSize;
	Cell cells[64];
	const Cell& cellAt(Vei2 brdPos) const;
	const Cell& cellAt(int x, int y) const;
	Cell& cellAt(int x, int y);
	Vei2 pieceScreenPos(int x, int y) const;
	void drawPawnReplacements(Side side, Graphics& gfx) const;
	void changeTurn();

private:
	const Color clr[2] = { Color(240,217,181),Color(181,136,99) };
	const Color highlightClr = Color(20, 140, 20);
	Surface piecesSprite = Surface("Sprites\\ChessPiecesArray320x120.bmp");
	Surface pepeSprite = Surface("Sprites\\Pepe75x75.bmp");
	void drawPepe(Graphics& gfx) const;

private:
	PieceManager table;
	void InitializePieces();

private:
	enum class GameState
	{
		Waiting,
		PieceSelected,
		PawnReplacement
	};
	GameState state = GameState::Waiting;
	struct Selected
	{
		Vei2 pos;
		std::vector<Vei2> validMoves;
	};
	Selected selectedPiece;
	Side turn = Side::White;
	bool isTurnInCheck = false;
	bool isTurnCheckMate = false;
};

