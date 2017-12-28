#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Surface.h"
#include "SpriteEffect.h"

enum class PieceType
{
	Queen,
	King,
	Rook,
	Knight,
	Bishop,
	Pawn
};

enum class PieceColor
{
	White,
	Black
};

class Piece
{
public:
	Piece() = default;
	Piece(PieceColor side, PieceType type, RectI whiteRect, RectI blackRect );
	void Draw(Vei2 pos, const Surface& surface, Graphics& gfx) const;
	PieceType GetType() const;
	PieceColor GetColor() const;
	//virtual std::vector<Vei2> possibleMoves(const class Board& brd) const = 0;

private:
	PieceColor clr;
	PieceType type;
	RectI rect[2]; //0 for white, 1 for black



public:
	const static int size = 60; //TO DO: make it sprite width / 6 
};

class Queen : public Piece
{
public:
	Queen(PieceColor clr);
};

class King : public Piece
{
public:
	King(PieceColor clr);
};

class Rook : public Piece //tura
{
public:
	Rook(PieceColor clr);
};

class Knight : public Piece
{
public:
	Knight(PieceColor clr);
};

class Bishop : public Piece //nebun
{
public:
	Bishop(PieceColor clr);
};

class Pawn : public Piece 
{
public:
	Pawn(PieceColor clr);
};