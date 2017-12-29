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
	void Draw(Vei2 pos, const Surface& surface, Graphics& gfx) const;
	Side GetSide() const;
	//virtual std::vector<Vei2> possibleMoves(std::vector<std::vector<Piece*>>) const = 0;

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
};

class King : public Piece
{
public:
	King(Side side);
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
};

class Bishop : public Piece //nebun
{
public:
	Bishop(Side side);
};

class Pawn : public Piece 
{
public:
	Pawn(Side side);
};