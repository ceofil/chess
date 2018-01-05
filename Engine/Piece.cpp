#include "Piece.h"
#include "PieceManager.h"

Piece::Piece(Side side, RectI whiteRectSprite, RectI blackRectSprite, bool isKing)
	:
	side(side),
	isKing(isKing)
{
		rect[(int)Side::White] = whiteRectSprite;
		rect[(int)Side::Black] = blackRectSprite;
}

void Piece::Draw(Vei2 pos, const Surface& surface, Graphics & gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, rect[(int)side], surface, SpriteEffect::Chroma{ Colors::Magenta });
}

Side Piece::GetSide() const
{
	return side;
}

std::vector<Vei2> Piece::PossibleMoves(const PieceManager& table, const  Vei2 pos) const
{
	return std::vector<Vei2>();
}

bool Piece::IsKing() const
{
	return isKing;
}

void Piece::Moved()
{
	hasMoved = true;
}

bool Piece::HasMoved() const
{
	return hasMoved;
}

King::King(Side side)
	:
	Piece(side, RectI(size, 2 * size, 0, size), RectI(size, 2 * size, size, 2 * size), true)
{
}

std::vector<Vei2> King::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	//kings can't get in each other's range
	Side otherSide = Side::Black;
	if (GetSide() == otherSide)
	{
		otherSide = Side::White;
	}
	const Vei2 otherKingPos = table.GetKingPos(otherSide);
	const auto isInOtherKingRange = [=](Vei2 mobile) 
	{
		return (std::abs(mobile.x - otherKingPos.x) <= 1 && (std::abs(mobile.y - otherKingPos.y) <= 1));
	};


	std::vector<Vei2> vec;
	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dy || dx)
			{
				Vei2 mobile = pos + Vei2( dx, dy );
				if (!isInOtherKingRange(mobile))
				{
					if (table.Contains(mobile))
					{
						const Piece* const p = table.GetPiece(mobile);
						if (p)
						{
							if (p->GetSide() != GetSide())
							{
								vec.push_back(mobile);
							}
						}
						else
						{
							vec.push_back(mobile);
						}
					}
				}
			}
		}
	}

	//rook swap case
	if (HasMoved() == false && table.IsKingAttacked(GetSide()) == false)
	{
		//normally I should check if it's a rook but if the piece is it at that position and it has not moved it is certainly a rook
		const Vei2 leftRookPos = Vei2(0, pos.y);
		const Piece* leftRook = table.GetPiece(leftRookPos);
		if (leftRook)
		{
			if (leftRook->HasMoved() == false)
			{
				bool isValid = true;
				for (int x = 1; x < 3; x++)
				{
					Vei2 posToCheck = pos - Vei2(x, 0);
					if (table.GetPiece(posToCheck) || table.IsValidMove(pos, posToCheck) == false || isInOtherKingRange(posToCheck))
					{
						isValid = false;
						break;
					}
				}
				if (isValid)
				{
					vec.push_back(leftRookPos);
				}
			}
		}
		
		const Vei2 rightRookPos = Vei2(7, pos.y);
		const Piece* rightRook = table.GetPiece(rightRookPos);
		if (rightRook)
		{
			if (rightRook->HasMoved() == false)
			{
				bool isValid = true;
				if (table.GetPiece(pos + Vei2(3, 0)))
				{
					isValid = false;
				}
				for (int x = 1; x < 3; x++)
				{
					Vei2 posToCheck = pos + Vei2(x, 0);
					if (table.GetPiece(posToCheck) || table.IsValidMove(pos, posToCheck) == false || isInOtherKingRange(posToCheck))
					{
						isValid = false;
						break;
					}
				}
				if (isValid)
				{
					vec.push_back(rightRookPos);
				}
			}
		}
	}
	return vec;
}

Queen::Queen(Side side)
	:
	Piece(side, RectI(0, size, 0, size), RectI(0, size, size, 2 * size))
{
}

std::vector<Vei2> Queen::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			if (dy || dx)
			{
				const Vei2 delta = { dx,dy };
				for (Vei2 mobile = pos + delta; table.Contains(mobile); mobile += delta)
				{
					const Piece* const p = table.GetPiece(mobile);
					if (p)
					{
						if (p->GetSide() != GetSide())
						{
							vec.push_back(mobile);
						}
						break;
					}
					else
					{
						vec.push_back(mobile);
					}
				}
			}
		}
	}
	return vec;
}

Rook::Rook(Side side)
	:
	Piece(side, RectI(2 * size, 3 * size, 0, size), RectI(2 * size, 3 * size, size, 2 * size))
{
}

std::vector<Vei2> Rook::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int d = -1; d <= 1; d += 2)
	{
		for (int n = 0; n <= 1; n++)
		{
			Vei2 delta;
			if (n)
			{
				delta = { 0,d };
			}
			else
			{
				delta = { d,0 };
			}
			for (Vei2 mobile = pos + delta; table.Contains(mobile); mobile += delta)
			{
				const Piece* const p = table.GetPiece(mobile);
				if (p)
				{
					if (p->GetSide() != GetSide())
					{
						vec.push_back(mobile);
					}
					break;
				}
				else
				{
					vec.push_back(mobile);
				}
			}
		}
	}
	return vec;
}

Knight::Knight(Side side)
	:
	Piece(side, RectI(3 * size, 4 * size, 0, size), RectI(3 * size, 4 * size, size, 2 * size))
{
}

std::vector<Vei2> Knight::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int dy = -1; dy <= 1; dy += 2)
	{
		for (int dx = -1; dx <= 1; dx += 2)
		{
			for (int n = 0; n <= 1; n++)
			{
				Vei2 delta;
				if (n)
				{
					delta = { 2 * dx,dy };
				}
				else
				{
					delta = { dx, 2 * dy };
				}
				Vei2 mobile = pos + delta;
				if (table.Contains(mobile))
				{
					const Piece* const p = table.GetPiece(mobile);
					if (p)
					{
						if (p->GetSide() != GetSide())
						{
							vec.push_back(mobile);
						}
					}
					else
					{
						vec.push_back(mobile);
					}
				}

			}
		}
	}
	return vec;
}

Bishop::Bishop(Side side)
	:
	Piece(side, RectI(4 * size, 5 * size, 0, size), RectI(4 * size, 5 * size, size, 2 * size))
{
}

std::vector<Vei2> Bishop::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int dy = -1; dy <= 1; dy += 2)
	{
		for (int dx = -1; dx <= 1; dx += 2)
		{
			const Vei2 delta = { dx,dy };
			for (Vei2 mobile = pos + delta; table.Contains(mobile); mobile += delta)
			{
				const Piece* const p = table.GetPiece(mobile);
				if (p)
				{
					if (p->GetSide() != GetSide())
					{
						vec.push_back(mobile);
					}
					break;
				}
				else
				{
					vec.push_back(mobile);
				}
			}
		}
	}
	return vec;
}

Pawn::Pawn(Side side)
	:
	Piece(side, RectI(5 * size, 6 * size, 0, size), RectI(5 * size, 6 * size, size, 2 * size))
{
	if (side == Side::Black)
	{
		sense = -1;
	}
	else
	{
		sense = 1;
	}
}

std::vector<Vei2> Pawn::PossibleMoves(const PieceManager& table, const Vei2 pos) const
{
	std::vector<Vei2> vec;
	
	int maxi = 2;
	if (HasMoved())
	{
		maxi = 1;
	}
	for (int dy = 1; dy <= maxi; dy++)
	{
		int left = -1;
		int right = 1;
		if (dy == 2)
		{
			left = right = 0;
		}
		for (int dx = left; dx <= right; dx++)
		{
			Vei2 mobile = pos + Vei2(dx, dy * sense);
			if (table.Contains(mobile))
			{
				const Piece* const p = table.GetPiece(mobile);
				if (dx)
				{
					if (p)
					{
						if (p->GetSide() != GetSide())
						{
							vec.push_back(mobile);
						}
					}
				}
				else
				{
					if (p == nullptr)
					{
						vec.push_back(mobile);
					}
				}
			}
		}
	}
	return vec;
}
