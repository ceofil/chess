#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Surface.h"
#include "SpriteEffect.h"

class Piece
{
public:
	Piece() = default;
	Piece(RectI whiteRect, RectI blackRect, int side);
	void Draw(Vei2 pos, const Surface& surface, Graphics& gfx) const;
	//virtual std::vector<Vei2> possibleMoves(const class Board& brd) const = 0;

private:
	RectI rect[2];
	int side; //0 for white, 1 for black


public:
	const static int size = 60; //TO DO: make it sprite width / 6 
};

class Queen : public Piece
{
public:
	Queen(int side);
};

class King : public Piece
{
public:
	King(int side);
};

class Rook : public Piece //tura
{
public:
	Rook(int side);
};

class Knight : public Piece
{
public:
	Knight(int side);
};

class Bishop : public Piece //nebun
{
public:
	Bishop(int side);
};

class Pawn : public Piece 
{
public:
	Pawn(int side);
};