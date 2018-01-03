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
	
	if (table.IsKingAttacked(Side::Black))
	{
		CellAt(table.GetKingPos(Side::Black)).Draw(gfx, Colors::Red);
	}
	if (table.IsKingAttacked(Side::White))
	{
		CellAt(table.GetKingPos(Side::White)).Draw(gfx, Colors::Red);
	}


	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (table.GetPiece({x,y}))
			{
				table.GetPiece({ x,y })->Draw(pieceScreenPos(x, y), sprite, gfx);
			}
		}
	}

	if (state == GameState::PieceSelected)
	{
		CellAt(selectedPiece.pos).DrawHighlight(gfx, highlightClr);
		for (Vei2 move : selectedPiece.validMoves)
		{
			CellAt(move).DrawMark(gfx, highlightClr);
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
		auto p = table.GetPiece(brdPos);

		switch (state)
		{
		case GameState::Waiting:
		{
			if (p)
			{
				selectedPiece.validMoves = table.ValidMoves(brdPos);
				selectedPiece.pos = brdPos;
				state = GameState::PieceSelected;
			}
			break;
		}
		case GameState::PieceSelected:
		{
			if (selectedPiece.pos == brdPos)
			{
				state = GameState::Waiting;
			}
			else
			{
				if (p)
				{
					if (p->GetSide() == table.GetPiece(selectedPiece.pos)->GetSide())
					{
						selectedPiece.validMoves = table.ValidMoves(brdPos);
						selectedPiece.pos = brdPos;
					}
					else
					{
						table.Transfer(selectedPiece.pos, brdPos);
						state = GameState::Waiting;
					}
				}
				else
				{
					table.Transfer(selectedPiece.pos, brdPos);
					state = GameState::Waiting;
				}
			}
			break;
		}
		}
	}
	else
	{
		state = GameState::Waiting;
	}
}

const Cell & Board::CellAt(Vei2 brdPos) const
{
	return CellAt(brdPos.x, brdPos.y);
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
		table.SetPiece(0, i * 7, new Rook((Side)i));
		table.SetPiece(1, i * 7, new Knight((Side)i));
		table.SetPiece(2, i * 7, new Bishop((Side)i));
		table.SetPiece(3, i * 7, new King((Side)i));
		table.SetPiece(4, i * 7, new Queen((Side)i));
		table.SetPiece(5, i * 7, new Bishop((Side)i));
		table.SetPiece(6, i * 7, new Knight((Side)i));
		table.SetPiece(7, i * 7, new Rook((Side)i));
		for (int j = 0; j < 8; j++)
		{
			table.SetPiece( j, 1 + i * 5 , new Pawn((Side)i));
		}
	}
}

