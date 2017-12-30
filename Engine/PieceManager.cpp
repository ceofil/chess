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
