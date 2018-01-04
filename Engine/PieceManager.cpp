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
	assert(ptr);
	Piece*& p = pieceAt(brdPos);
	if (p)
	{
		delete p;
	}
	p = ptr;
}

void PieceManager::SetPiece(int x, int y, Piece * ptr)
{
	SetPiece(Vei2(x, y), ptr);
}

void PieceManager::Transfer(Vei2 giverPos, Vei2 receiverPos)
{
	Piece*& receiver = pieceAt(receiverPos);
	Piece*& giver = pieceAt(giverPos);
	SetPiece(receiverPos, giver);
	pieceAt(giverPos) = nullptr;
	pieceAt(receiverPos)->Moved();
}

void PieceManager::DoCastle(Vei2 kingPos, Vei2 rookPos)
{
	const int y = rookPos.y; 
	if (rookPos.x == 0)
	{
		Transfer(kingPos, Vei2(1, y));
		Transfer(rookPos, Vei2(2, y));
	}
	else
	{
		Transfer(kingPos, Vei2(5, y));
		Transfer(rookPos, Vei2(4, y));
	}
}

const Piece * const PieceManager::GetPiece(Vei2 brdPos) const
{
	assert(Contains(brdPos));
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

Vei2 PieceManager::GetKingPos(Side side) const
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			const Piece* p = GetPiece({ x,y });
			if (p)
			{
				if (p->IsKing() && p->GetSide() == side)
				{
					return { x,y };
				}
			}
		}
	}
	return Vei2();
}

bool PieceManager::IsKingAttacked(Side side) const
{
	const Vei2 kingPos = GetKingPos(side);
	
	//checks for Rooks, Queens, Pawns and Bishops
	std::vector<Vei2> possibleAttackerPos;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i || j)
			{
				const Vei2 delta = { j,i };
				for (Vei2 mobile = kingPos + delta; Contains(mobile); mobile += delta)
				{
					const Piece* p = GetPiece(mobile);
					if (p)
					{
						if (p->GetSide() != side)
						{
							possibleAttackerPos.push_back(mobile);
						}
						break;
					}
				}
			}
		}
	}
	for (Vei2 attackerPos : possibleAttackerPos)
	{
		const Piece* attacker = GetPiece(attackerPos);

		/*
			King::PossibleMoves calls PieceManager::IsKingAttacked ( because a king can't pass through check when castling )
			So I avoid that because it would cause infinite recursion and kings can't get in each other's range anyway, it's illegal.
		*/
		if (attacker->IsKing() == false)
		{
			std::vector<Vei2> attackerRange = attacker->PossibleMoves(*this, attackerPos);  
			for (Vei2 move : attackerRange)
			{
				if (kingPos == move)
				{
					return true;
				}
			}
		}
	}
	
	//checks for Knights
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			for (int n = 0; n <= 1; n++)
			{
				Vei2 delta;
				if (n)
				{
					delta = { 2 * j,i };
				}
				else
				{
					delta = { j, 2 * i };
				}
				Vei2 mobile = kingPos + delta;
				if (Contains(mobile))
				{
					const Piece* const p = GetPiece(mobile);
					if (p)
					{
						if (p->GetSide() != side)
						{
							if (const Knight* pKnight = dynamic_cast<const Knight*>(p))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

std::vector<Vei2> PieceManager::ValidMoves(Vei2 brdPos) const
{
	std::vector<Vei2> validMoves;

	for (Vei2 move : GetPiece(brdPos)->PossibleMoves(*this, brdPos))
	{
		if (IsValidMove(brdPos, move))
		{
			validMoves.push_back(move);
		}
	}
	return validMoves;
}

bool PieceManager::IsValidMove(Vei2 brdPos, Vei2 move) const
{
	assert(brdPos != move);
	//using const_cast because I'm just swaping the pointers around but in the end everything is unchanged
	Piece*& giver = const_cast<PieceManager*>(this)->pieceAt(brdPos);
	Piece*& receiver = const_cast<PieceManager*>(this)->pieceAt(move);
	Piece* receiverCopy = receiver;

	Side side = giver->GetSide();

	receiver = giver;
	giver = nullptr;

	bool isValid = !(IsKingAttacked(side));

	giver = receiver;
	receiver = receiverCopy;

	return isValid;
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
