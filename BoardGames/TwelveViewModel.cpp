#include "pch.h"
#include "TwelveViewModel.h"

void CTwelveViewModel::SetGame(CPoint WinSize)
{
	model.MakeGridBoard(WinSize);
}

std::tuple<CRect*, int, CGameTool::CLog*, int> CTwelveViewModel::Game(CPoint WinSize)
{
	CRect** rectBoard = model.getGridBoardRect();

	int col = model.getGridBoardSize().x;
	int row = model.getGridBoardSize().y;

	//2차원 배열을 1차원 배열에 저장
	CRect* rect = new CRect[col * row];
	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			rect[c * row + r] = rectBoard[c][r];
		}
	}

	CGameTool::CSpace** spaceBoard = model.getGridBoard();
	CGameTool::CLog* log;
	CString text;

	//격자판 로그 생성
	log = new CGameTool::CLog[col * row];
	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			log[c * row + r].setPoint(spaceBoard[c][r].getPoint());
			text.Format(_T("%d, %d"), log[c * row + r].getPoint().x, log[c * row + r].getPoint().y);
			log[c * row + r].setText(text);
		}
	}

	return std::make_tuple(rect, 12, log, 12);
}