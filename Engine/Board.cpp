#include "Board.h"

Board::Board(RectI rect)
	:
	rect(rect)
{
	cellSize = (rect.GetWidth() + 1) / 8;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			CellAt(x, y) = Cell(
				RectI(
					rect.left + x * cellSize,
					rect.left + (x + 1) * cellSize,
					rect.top + y * cellSize,
					rect.top + (y + 1) * cellSize
				));
		}
	}
	InitializePieces();
}

void Board::Draw(Graphics & gfx) const
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			const Cell& c = CellAt(x, y);
			c.Draw(gfx, clr[(x + y) % 2]);
		}
	}

	if (state == GameState::PieceSelected)
	{
		CellAt(selectedPiece.x, selectedPiece.y).Draw(gfx, Colors::Red);
	}
	
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (table.pieces[y][x])
			{
				table.pieces[y][x]->Draw(pieceScreenPos(x, y), sprite, gfx);
			}
		}
	}
}

void Board::HandleMousePressed(Vei2 screenPos)
{
	if (rect.Contains(screenPos))
	{
		screenPos -= {rect.left, rect.top};

		const int row = screenPos.y / cellSize;
		const int col = screenPos.x / cellSize;
		Vei2 brdPos = Vei2(col, row);

		switch (state)
		{
		case GameState::Waiting:
		{
			if (table.pieces[row][col])
			{
				selectedPiece = Vei2(col, row);
				state = GameState::PieceSelected;
			}
			break;
		}
		case GameState::PieceSelected:
		{
			if (selectedPiece == brdPos)
			{
				state = GameState::Waiting;
			}
			break;
		}
		}

	}
}

const Cell & Board::CellAt(int x, int y) const
{
	return cells[y * 8 + x];
}

Cell & Board::CellAt(int x, int y)
{
	return cells[y * 8 + x];
}

Vei2 Board::pieceScreenPos(int x, int y) const 
{
	return CellAt(x, y).GetRect().GetCenter() - Vei2(30, 30);
}

void Board::InitializePieces()
{
	for (int i = 0; i <= 1; i++)
	{
		table.pieces[i * 7][0] = new Rook((Side)i);
		table.pieces[i * 7][1] = new Knight((Side)i);
		table.pieces[i * 7][2] = new Bishop((Side)i);
		table.pieces[i * 7][3] = new King((Side)i);
		table.pieces[i * 7][4] = new Queen((Side)i);
		table.pieces[i * 7][5] = new Bishop((Side)i);
		table.pieces[i * 7][6] = new Knight((Side)i);
		table.pieces[i * 7][7] = new Rook((Side)i);
		for (int j = 0; j < 8; j++)
		{
			table.pieces[1 + i * 5][j] = new Pawn((Side)i);
		}
	}
}

