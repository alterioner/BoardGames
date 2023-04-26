#include "pch.h"
#include "TwelveViewModel.h"

void CTwelveViewModel::ReadyGame(CPoint winSize)
{
	Model.MakeGridBoard(winSize);
	Model.MakeItem();
	Model.MakeCatchSpace();
}

void CTwelveViewModel::ResetGame()
{
	Model.ResetGridBoard();
	Model.ResetItem();
	Model.ResetCatchSpace();
}

bool CTwelveViewModel::DoGame(CPoint clickPoint)
{
	this->ClickPoint = clickPoint;
	if (!Model.getAnimating())
	{
		Model.Game(clickPoint);
		return Model.getAnimating();
	}
	else
	{
		return Model.Animation();
	}
}

std::tuple<CRect*, int> CTwelveViewModel::DrawRectInfo()
{
	int col = Model.getGridRectSize().x;
	int row = Model.getGridRectSize().y;

	CRect** rectBoard = Model.getGridRect();

	CRect* rect = new CRect[col * row];

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			rect[c * row + r] = rectBoard[c][r];
		}
	}

	return std::make_tuple(rect, col * row);
}

std::tuple<CString*, CPoint*, int> CTwelveViewModel::DrawImageInfo()
{
	CGameTool::CItem** item = Model.getItem();

	CString* filePath = new CString[8];
	CPoint* imagePoint = new CPoint[8];

	for (int job = 0; job < 4; job++)
	{
		for (int side = 0; side < 2; side++)
		{
			filePath[job * 2 + side] = L"res/Twelve/" + item[job][side].getSide() + L"/" + item[job][side].getJob();	//파일 경로 설정
			if (item[job][side].getPlace() == L"Catch") filePath[job * 2 + side] += L"_Taken.png";	//아이템이 속한 장소에 따라 파일명 변경
			else filePath[job * 2 + side] += L".png";

			imagePoint[job * 2 + side] = item[job][side].getPoint();
		}
	}

	return std::make_tuple(filePath, imagePoint, 8);
}

std::tuple<CGameTool::CLog*, int> CTwelveViewModel::DrawLogInfo()
{
	CString text;
	CPoint point;

	int col = Model.getGridRectSize().x;
	int row = Model.getGridRectSize().y;
	int extra = 6;

	CGameTool::CSpace** spaceBoard = Model.getGridSpace();

	CGameTool::CLog* log = new CGameTool::CLog[col * row + extra];

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

	//임시
	log[12].setPoint(CPoint(1180, 0));
	text.Format(_T("temp : CPoint(%d, %d)"), Model.temp.x, Model.temp.y);
	log[12].setText(text);
	log[12].setAlign(3);

	//격자판 크기 확인
	log[13].setPoint(CPoint(10, 0));
	text.Format(_T("Grid Size : CPoint(%d, %d)"), Model.getGridRectSize().x, Model.getGridRectSize().y);
	log[13].setText(text);
	log[13].setAlign(1);

	//마우스가 클릭한 좌표 확인
	log[14].setPoint(CPoint(10, 20));
	text.Format(_T("Click Point : CPoint(%d, %d)"), ClickPoint.x, ClickPoint.y);
	log[14].setText(text);
	log[14].setAlign(1);

	//활성화된 아이템 인덱스 확인
	log[15].setPoint(CPoint(10, 40));
	if ((point = Model.getActiveItemIndex()) == CPoint(NONE, NONE)) log[15].setText(L"Active Item Index : NONE");
	else
	{
		text.Format(_T("Active Item Index : CPoint(%d, %d)"), point.x, point.y);
		log[15].setText(text);
	}
	log[15].setAlign(1);

	//활성화된 격자판의 인덱스 확인
	log[16].setPoint(CPoint(10, 60));
	if ((point = Model.getActiveGridSpaceIndex()) == CPoint(NONE, NONE)) log[16].setText(L"Active Grid Index : NONE");
	else
	{
		text.Format(_T("Active Grid Index : CPoint(%d, %d)"), point.x, point.y);
		log[16].setText(text);
	}
	log[16].setAlign(1);

	//currentStatus 확인
	log[17].setPoint(CPoint(10, 80));
	text.Format(_T("strCurrentStatus : %d"), Model.getCurrentStatus());
	log[17].setText(text);
	log[17].setAlign(1);

	return std::make_tuple(log, col * row + extra);
}