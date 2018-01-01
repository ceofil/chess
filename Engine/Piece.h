#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Surface.h"
#include "SpriteEffect.h"
#include <vector>

enum class Side
{
	White,
	Black
};

class Piece
{
public:
	Piece() = default;
	Piece(Side side, RectI whiteRectSprite, RectI blackRectSprite, bool isKing = false );
	virtual ~Piece() = default;
	void Draw(Vei2 pos, const Surface& surface, Graphics& gfx) const;
	Side GetSide() const;
	// this will be become abstract after I override it for all derived classes
	virtual std::vector<Vei2> possibleMoves(class PieceManager table, Vei2 pos) const;

private:
	Side side;
	bool isKing;
	RectI rect[2]; //0 for white, 1 for black



public:
	const static int size = 60; //TO DO: make it sprite width / 6 
};

class Queen : public Piece
{
public:
	Queen(Side side);
	std::vector<Vei2> possibleMoves(class PieceManager table, Vei2 pos) const override;
};

class King : public Piece
{
public:
	King(Side side);
	std::vector<Vei2> possibleMoves(class PieceManager table, Vei2 pos) const override;
};

class Rook : public Piece //tura
{
public:
	Rook(Side side);
};

class Knight : public Piece
{
public:
	Knight(Side side);
	std::vector<Vei2> possibleMoves(class PieceManager table, Vei2 pos) const override;
};

class Bishop : public Piece //nebun
{
public:
	Bishop(Side side);
	std::vector<Vei2> possibleMoves(class PieceManager table, Vei2 pos) const override;
};

class Pawn : public Piece 
{
public:
	Pawn(Side side);
};