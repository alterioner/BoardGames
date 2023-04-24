#include "pch.h"
#include "TwelveViewModel.h"

void CTwelveViewModel::SetGame(CPoint WinSize)
{
	model.setGridSize(CPoint(100, 100));
	model.setGridBoardSize(CPoint(3, 4));
	model.MakeGridBoard(WinSize);
}

std::tuple<CRect*, int> CTwelveViewModel::Game(CPoint WinSize)
{

	CRect** rectBoard = model.getGridBoardRect();

	int col = model.getGridSize().x;
	int row = model.getGridSize().y;

	CRect* rect = new CRect[col + row];
	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			rect[(c * 4) + r] = rectBoard[c][r];
		}
	}

	return std::make_tuple(rect, 12);
}