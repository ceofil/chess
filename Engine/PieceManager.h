#pragma once
#include "Piece.h"

struct PieceManager
{
	PieceManager() = default;
	PieceManager( const PieceManager& other );
	PieceManager& operator=(const PieceManager& other);
	~PieceManager();

	//can't auto this for some reason
	std::vector<std::vector<Piece*>> pieces = \
	std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr));
};