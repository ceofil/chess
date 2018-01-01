#include "PieceManager.h"
#include <algorithm>

PieceManager::PieceManager(const PieceManager & other)
{
	std::transform(other.pieces.begin(),other.pieces.end(),pieces.begin(),
	[](Piece* p) -> Piece*
	{
		if(p)
		{
			return new Piece(*p);
		}
		else return nullptr;
	});
}

PieceManager & PieceManager::operator=(const PieceManager & other)
{
	std::for_each(pieces.begin(), pieces.end(),
	[](Piece*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	});

	std::transform(other.pieces.begin(), other.pieces.end(), pieces.begin(),
	[](Piece* p) -> Piece*
	{
		if (p)
		{
			return new Piece(*p);
		}
		else return nullptr;
	});

	return *this;
}

PieceManager::~PieceManager()
{
	std::for_each(pieces.begin(), pieces.end(),
	[](Piece*& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	});
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
	return pieces[brdPos.y * 8 + brdPos.x];
}

bool PieceManager::Contains(int x, int y) const
{
	return x >= 0 && y >= 0 && x < 8 && y < 8;
}

bool PieceManager::Contains(Vei2 brdPos) const
{
	return Contains(brdPos.x,brdPos.y);
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

Piece *& PieceManager::pieceAt(int x, int y)
{
	assert(Contains(x,y));
	return pieces[y * 8 + x];
}

Piece*& PieceManager::pieceAt(Vei2 brdPos)
{
	return pieceAt(brdPos.x, brdPos.y);
}
