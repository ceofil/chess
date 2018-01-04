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

std::vector<Vei2> Piece::PossibleMoves(const PieceManager& table, Vei2 pos) const
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

std::vector<Vei2> King::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i || j)
			{
				Vei2 mobile = pos + Vei2( j, i );
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

Queen::Queen(Side side)
	:
	Piece(side, RectI(0, size, 0, size), RectI(0, size, size, 2 * size))
{
}

std::vector<Vei2> Queen::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i || j)
			{
				const Vei2 delta = { j,i };
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

std::vector<Vei2> Rook::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int i = -1; i <= 1; i += 2)
	{
		for (int n = 0; n <= 1; n++)
		{
			Vei2 delta;
			if (n)
			{
				delta = { 0,i };
			}
			else
			{
				delta = { i,0 };
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

std::vector<Vei2> Knight::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
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

std::vector<Vei2> Bishop::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = -1; j <= 1; j += 2)
		{
			const Vei2 delta = { j,i };
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

std::vector<Vei2> Pawn::PossibleMoves(const PieceManager& table, Vei2 pos) const
{
	std::vector<Vei2> vec;
	
	int maxi = 2;
	if (HasMoved())
	{
		maxi = 1;
	}
	for (int i = 1; i <= maxi; i++)
	{
		int left = -1;
		int right = 1;
		if (i == 2)
		{
			left = right = 0;
		}
		for (int j = left; j <= right; j++)
		{
			Vei2 mobile = pos + Vei2(j, i * sense);
			if (table.Contains(mobile))
			{
				const Piece* const p = table.GetPiece(mobile);
				if (j)
				{
					if (p)
					{
						if (p->GetSide() != GetSide() && j)
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
