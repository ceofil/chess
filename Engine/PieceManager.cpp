#include "PieceManager.h"

PieceManager::PieceManager(const PieceManager & other)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (other.pieces[i][j])
			{
				pieces[i][j] = new Piece(*(other.pieces[i][j]));
			}
		}
	}
}

PieceManager & PieceManager::operator=(const PieceManager & other)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces[i][j])
			{
				delete pieces[i][j];
				pieces[i][j] = nullptr;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (other.pieces[i][j])
			{
				pieces[i][j] = new Piece(*(other.pieces[i][j]));
			}
		}
	}
	return *this;
}

PieceManager::~PieceManager()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pieces[i][j])
			{
				delete pieces[i][j];
				pieces[i][j] = nullptr;
			}
		}
	}
}

void PieceManager::SetPiece(Vei2 brdPos, Piece * ptr)
{
	Piece*& p = pieceAt(brdPos);
	if (pieceAt(brdPos) != nullptr)
	{
		RemovePiece(brdPos);
	}
	p = ptr;
}

void PieceManager::SetPiece(int x, int y, Piece * ptr)
{
	SetPiece(Vei2(x, y), ptr);
}

void PieceManager::Transfer(Vei2 giverPos, Vei2 receiverPos)
{
	SetPiece(receiverPos, pieceAt(giverPos));
	RemovePiece(giverPos);
}

const Piece * const PieceManager::GetPiece(Vei2 brdPos) const
{
	return pieces[brdPos.y][brdPos.x];
}

void PieceManager::RemovePiece(Vei2 brdPos)
{
	Piece*& p = pieceAt(brdPos);
	if (p != nullptr)
	{
		delete p;
	}
	p = nullptr;
}

Piece*& PieceManager::pieceAt(Vei2 brdPos)
{
	return pieces[brdPos.y][brdPos.x];
}
