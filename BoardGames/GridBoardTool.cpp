#include "pch.h"
#include "GridBoardTool.h"

CRect** CGridBoardTool::MakeGridRect(CPoint winSize, CPoint gridSize, CPoint gridRectSize)
{
	int width = gridSize.x;
	int heigtht = gridSize.y;

	int col = gridRectSize.x;
	int row = gridRectSize.y;

	int totalwidth = col * width;		//그려질 판의 넓이
	int totalheight = row * heigtht;	//그려질 판의 높이

	int startX = (winSize.x / 2) - (totalwidth / 2);	//보드가 그려지기 시작할 위치(위쪽 픽셀)
	int startY = (winSize.y / 2) - (totalheight / 2);	//보드가 그려지기 시작할 위치(왼쪽 픽셀)

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

CGameTool::CSpace** CGridBoardTool::MakeGridSpace(CPoint winSize, CPoint gridSize, CPoint gridSpaceSize, bool focusPoint)
{
	int width = gridSize.x;
	int height = gridSize.y;

	int col = gridSpaceSize.x;
	int row = gridSpaceSize.y;

	int totalWidth = col * width;
	int totalHeight = row * height;

	int startX = (winSize.x / 2) - (totalWidth / 2);
	int startY = (winSize.y / 2) - (totalHeight / 2);

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

//좌표를 받아 해당 좌표의 격자칸 인덱스 반환
CPoint CGridBoardTool::PointToGridSpaceIndex(CSpace** gridSpace, CPoint gridSpaceSize, CPoint clickPoint)
{
	int col = gridSpaceSize.x;
	int row = gridSpaceSize.y;

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			if (PtInRect(gridSpace[c][r].getRect(), clickPoint)) return CPoint(c, r);
		}
	}

	return CPoint(NONE, NONE);
}

//출발지 격자칸 인덱스와 도착지 격자칸 인덱스를 입력받아 격자칸 아이템 인덱스 정보 갱신
void CGridBoardTool::MoveSpaceInfo(CSpace** gridSpace, CPoint originalIndex, CPoint nextIndex)
{
	CPoint itemIndex = gridSpace[originalIndex.x][originalIndex.y].getItemIndex();
	gridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	gridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}
