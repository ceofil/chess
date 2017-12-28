#include "Board.h"

Board::Board(RectI rect)
{
	const int cellWidth = (rect.GetWidth() + 1) / width;
	const int cellHeight = (rect.GetHeight() + 1) / height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			cells[y*width + x] = Cell(
				RectI(
					rect.left + x * cellWidth,
					rect.left + (x + 1) * cellWidth,
					rect.top + y * cellHeight,
					rect.top + (y + 1) * cellHeight
				));
		}
	}
	InitializePieces();
}

void Board::Draw(Graphics & gfx) const
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			const Cell& c = CellAt(x, y);
			c.Draw(gfx, clr[(x + y) % 2]);
			if (c.IsOccupied())
			{
				c.GetPiece()->Draw(c.GetRect().GetCenter() + Vei2{ -30,-30 }, sprite, gfx);
			}
		}
	}
}

Board::~Board()
{
	for (Piece* p : whitePieces)
	{
		delete p;
	}
	for (Piece* p : blackPieces)
	{
		delete p;
	}
}

const Cell & Board::CellAt(int x, int y) const
{
	return cells[y * width + x];
}

Cell & Board::CellAt(int x, int y)
{
	return cells[y * width + x];
}

void Board::AddPiece(int x, int y, Piece * ptr)
{
	Cell& c = CellAt(x, y);
	assert(!c.IsOccupied());
	c.SetPiece(ptr);

	if (ptr->GetColor() == PieceColor::White)
	{
		whitePieces.push_back(ptr);
	}
	else
	{
		blackPieces.push_back(ptr);
	}
}

void Board::InitializePieces()
{
	AddPiece(3, 7, new Queen(PieceColor::White));
	AddPiece(4, 7, new King(PieceColor::White));
	AddPiece(0, 7, new Rook(PieceColor::White));
	AddPiece(7, 7, new Rook(PieceColor::White));
	AddPiece(1, 7, new Knight(PieceColor::White));
	AddPiece(6, 7, new Knight(PieceColor::White));
	AddPiece(2, 7, new Bishop(PieceColor::White));
	AddPiece(5, 7, new Bishop(PieceColor::White));
	for (int i = 0; i < 8; i++)
	{
		AddPiece(i, 6, new Pawn(PieceColor::White));
	}


	AddPiece(3, 0, new Queen(PieceColor::Black));
	AddPiece(4, 0, new King(PieceColor::Black));
	AddPiece(0, 0, new Rook(PieceColor::Black));
	AddPiece(7, 0, new Rook(PieceColor::Black));
	AddPiece(1, 0, new Knight(PieceColor::Black));
	AddPiece(6, 0, new Knight(PieceColor::Black));
	AddPiece(2, 0, new Bishop(PieceColor::Black));
	AddPiece(5, 0, new Bishop(PieceColor::Black));
	for (int i = 0; i < 8; i++)
	{
		AddPiece(i, 1, new Pawn(PieceColor::Black));
	}
}
