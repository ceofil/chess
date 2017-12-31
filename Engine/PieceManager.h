#pragma once
#include "Piece.h"

class PieceManager
{
public:
	PieceManager() = default;
	PieceManager( const PieceManager& other );
	PieceManager& operator=(const PieceManager& other);
	~PieceManager();
	void SetPiece(Vei2 brdPos, Piece* ptr);
	void SetPiece(int x, int y, Piece* ptr);
	void Transfer(Vei2 giverPos, Vei2 receiverPos);
	const Piece * const  GetPiece(Vei2 brdPos) const; 

private:
	Piece*& pieceAt(Vei2 brdPos);
	void RemovePiece(Vei2 brdPos);


	//can't auto this for some reason
private:
	std::vector<std::vector<Piece*>> pieces = \
	std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr));
};