#include "pch.h"
#include "GridBoardTool.h"

CRect** CGridBoardTool::MakeGridBoardRect(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize)
{
	int col = GridBoardSize.x;
	int row = GridBoardSize.y;

	int width = GridSize.x;
	int heigtht = GridSize.y;

	int totalwidth = col * width;		//그려질 판의 넓이
	int totalheight = row * heigtht;	//그려질 판의 높이

	int startX = (WinSize.x / 2) - (totalwidth / 2);	//보드가 그려지기 시작할 위치(위쪽 픽셀)
	int startY = (WinSize.y / 2) - (totalheight / 2);	//보드가 그려지기 시작할 위치(왼쪽 픽셀)

	CRect** rectBoard = new CRect * [col];
	for (int c = 0; c < col; c++)
	{
		rectBoard[c] = new CRect[row];
		for (int r = 0; r < row; r++)
		{
			rectBoard[c][r] = CRect(startX + (width * c), startY + (heigtht * r), startX + (width * (c + 1)), startY + (heigtht * (r + 1)));
		}
	}

	return rectBoard;
}

CGameTool::CSpace** CGridBoardTool::MakeGridBoardSpace(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize, bool focusPoint)
{
	int col = GridBoardSize.x;
	int row = GridBoardSize.y;

	int width = GridSize.x;
	int height = GridSize.y;

	int totalWidth = col * width;
	int totalHeight = row * height;

	int startX = (WinSize.x / 2) - (totalWidth / 2);
	int startY = (WinSize.y / 2) - (totalHeight / 2);

	CSpace** spaceBoard;
	if (focusPoint)
	{
		col++; row++;

		spaceBoard = new CGameTool::CSpace * [col];
		for (int c = 0; c < col; c++)
		{
			spaceBoard[c] = new CGameTool::CSpace[row];
			for (int r = 0; r < row; r++)
			{
				spaceBoard[c][r].setPoint(CPoint(startX + (width * c), startY + (height * r)));
				spaceBoard[c][r].setRect(PointToRect(spaceBoard[c][r].getPoint(), CPoint(width, height)));
			}
		}
	}
	else
	{
		spaceBoard = new CGameTool::CSpace * [col];
		for (int c = 0; c < col; c++)
		{
			spaceBoard[c] = new CGameTool::CSpace[row];
			for (int r = 0; r < row; r++)
			{
				spaceBoard[c][r].setPoint(CPoint(startX + (width * c) + (width / 2), startY + (height * r) + (height / 2)));
				spaceBoard[c][r].setRect(PointToRect(spaceBoard[c][r].getPoint(), CPoint(width, height)));
			}
		}
	}

	return spaceBoard;
}