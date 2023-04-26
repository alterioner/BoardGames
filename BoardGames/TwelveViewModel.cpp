#include "pch.h"
#include "TwelveViewModel.h"

void CTwelveViewModel::SetGame(CPoint WinSize)
{
	model.MakeGridBoard(WinSize);
	model.MakeItem();
	model.ResetGridBoard();
	model.ResetItem();
}

std::tuple<CRect*, int> CTwelveViewModel::DrawRectInfo()
{

	int col = model.getGridRectSize().x;
	int row = model.getGridRectSize().y;

	CRect** rectBoard = model.getGridRect();

	CRect* rect = new CRect[col * row];

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			rect[c * row + r] = rectBoard[c][r];
		}
	}

	return std::make_tuple(rect, 12);
}

std::tuple<CString*, CPoint*, int> CTwelveViewModel::DrawImageInfo()
{
	CGameTool::CItem** item = model.getItem();

	CString* filePath = new CString[8];
	CPoint* imagePoint = new CPoint[8];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			filePath[i * 2 + j] = L"res/Twelve/" + item[i][j].getSide() + L"/" + item[i][j].getJob();
			if (item[i][j].getPlace() == L"Catch") filePath[i * 2 + j] += L"_Taken.png";
			else filePath[i * 2 + j] += L".png";

			imagePoint[i * 2 + j] = item[i][j].getPoint();
		}
	}

	return std::make_tuple(filePath, imagePoint, 8);
}

std::tuple<CGameTool::CLog*, int> CTwelveViewModel::DrawLogInfo()
{
	CString text;

	int col = model.getGridRectSize().x;
	int row = model.getGridRectSize().y;

	CGameTool::CSpace** spaceBoard = model.getGridSpace();

	CGameTool::CLog* log = new CGameTool::CLog[col * row + 1];

	//각 격자판에 위치한 아이템 인덱스 표시

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			log[c * row + r].setPoint(spaceBoard[c][r].getPoint());
			if (spaceBoard[c][r].getItemIndex() == CPoint(NONE, NONE)) log[c * row + r].setText(L"NONE");
			else
			{
				text.Format(_T("%d, %d"), spaceBoard[c][r].getItemIndex().x, spaceBoard[c][r].getItemIndex().y);
				log[c * row + r].setText(text);
			}
			log[c * row + r].setAlign(2);
		}
	}

	//격자판 크기 확인
	log[12].setPoint(CPoint(10, 10));
	text.Format(_T("GridSize CPoint(%d, %d)"), model.getGridRectSize().x, model.getGridRectSize().y);
	log[12].setText(text);
	log[12].setAlign(1);

	return std::make_tuple(log, 13);
}