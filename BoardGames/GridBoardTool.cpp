#include "pch.h"
#include "GridBoardTool.h"

//윈도우 크기와, 한 칸의 크기와, 칸 개수를 받아 격자판을 만든다
CRect** CGridBoardTool::MakeGridBoardRect(CPoint WinSize, CPoint GridSize, CPoint GridBoardSize)
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