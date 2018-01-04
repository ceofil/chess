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
	const Piece * const GetPiece(Vei2 brdPos) const;
	bool Contains(int x, int y) const;
	bool Contains(Vei2 brdPos) const;
	Vei2 GetKingPos(Side side) const;
	bool IsKingAttacked(Side side) const;
	std::vector<Vei2> ValidMoves(Vei2 brdPos) const;
	bool IsValidMove(Vei2 brdPos, Vei2 move) const;


private:
	Piece*& pieceAt(int x, int y);
	Piece*& pieceAt(Vei2 brdPos);

private:
	std::vector<Piece*> pieces = std::vector<Piece*>(64, nullptr);
};