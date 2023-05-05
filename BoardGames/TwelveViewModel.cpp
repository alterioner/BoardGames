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
	Model.ResetStatus();
}

bool CTwelveViewModel::DoGame(CPoint clickPoint)
{
	this->ClickPoint = clickPoint;
	if (!Model.getAnimating())
	{
		Model.Game(clickPoint);
		if (Model.getAnimating()) return Model.Animation();	//Animation 한번 실행 후 반환
		else return false;
	}
	else
	{
		return Model.Animation();
	}
}

std::list<CRect> CTwelveViewModel::DrawRectInfo()
{
	std::list<CRect> rectList;

	int col = Model.getGridRectSize().x;
	int row = Model.getGridRectSize().y;

	CRect** rectBoard = Model.getGridRect();

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			rectList.emplace_back(rectBoard[c][r]);
		}
	}

	return rectList;
}

std::list<CGameTool::CImage> CTwelveViewModel::DrawImageInfo()
{
	std::list<CGameTool::CImage> imageList;
	CString filePath;
	CPoint point;

	CGameTool::CItem** item = Model.getItem();

	for (int job = 0; job < 4; job++)
	{
		for (int side = 0; side < 2; side++)
		{
			filePath = L"res/Twelve/" + item[job][side].getSide() + item[job][side].getJob() + item[job][side].getStatus() + L".png";	//파일 경로 설정
			point = item[job][side].getPoint();
			imageList.emplace_back(filePath, point);
		}
	}

	CPoint lastItemIndex = Model.getAnimatingItemIndex();

	if (lastItemIndex != CPoint(NONE, NONE))
	{
		int lastImageIndex = lastItemIndex.x * 2 + lastItemIndex.y;

		auto it = imageList.begin();
		advance(it, lastImageIndex);
		imageList.push_back(*it);
		imageList.erase(it);
	}

	return imageList;
}

std::list<CGameTool::CLog> CTwelveViewModel::DrawLogInfo()
{
	std::list<CGameTool::CLog> logList;

	CString text;
	CPoint point;

	int col = Model.getGridRectSize().x;
	int row = Model.getGridRectSize().y;

	CGameTool::CSpace** spaceBoard = Model.getGridSpace();

	//각 격자판에 위치한 아이템 인덱스 표시
	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			if (spaceBoard[c][r].getItemIndex() == CPoint(NONE, NONE)) text = L"NONE";
			else
			{
				text.Format(_T("%d, %d"), spaceBoard[c][r].getItemIndex().x, spaceBoard[c][r].getItemIndex().y);
			}
			logList.emplace_back(text, spaceBoard[c][r].getPoint(), 2);
		}
	}

	int leftLine = 0;
	int rigthLine = 0;

	//격자판 크기 확인
	text.Format(_T("Grid Rect Size : CPoint(%d, %d)"), Model.getGridRectSize().x, Model.getGridRectSize().y);
	logList.emplace_back(text, CPoint(1180, rigthLine * 20), 3);
	rigthLine++;

	//마우스가 클릭한 좌표 확인
	text.Format(_T("Click Point : CPoint(%d, %d)"), ClickPoint.x, ClickPoint.y);
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//Turn 확인
	logList.emplace_back(L"Turn: " + Model.getTurn(), CPoint(10, leftLine * 20), 1);
	leftLine++;

	//GameStatus 확인
	text.Format(_T("GameStatusQueue : %d"), Model.getGameStatusQueue());
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//활성화된 아이템 인덱스 확인
	if ((point = Model.getActiveItemIndex()) == CPoint(NONE, NONE)) text = L"Active Item Index : NONE";
	else
	{
		text.Format(_T("Active Item Index : CPoint(%d, %d)"), point.x, point.y);
	}
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//활성화된 격자판의 인덱스 확인
	if ((point = Model.getActiveGridSpaceIndex()) == CPoint(NONE, NONE)) text = L"Active Grid Index : NONE";
	else
	{
		text.Format(_T("Active Grid Index : CPoint(%d, %d)"), point.x, point.y);
	}
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//잡히는 아이템 인덱스 확인
	if ((point = Model.getCatchItemIndex()) == CPoint(NONE, NONE)) text = L"Catch Item Index : NONE";
	else
	{
		text.Format(_T("Catch Item Index : CPoint(%d, %d)"), point.x, point.y);
	}
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//움직이는 아이템 인덱스 확인
	if ((point = Model.getAnimatingItemIndex()) == CPoint(NONE, NONE)) text = L"Animating Item Index : NONE";
	else
	{
		text.Format(_T("Animating Item Index : CPoint(%d, %d)"), point.x, point.y);
	}
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//AnimationFrame 확인
	text.Format(_T("AnimationFrame : %d"), Model.getAnimationFrame());
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//OriginalPoint 확인
	text.Format(_T("OriginalPoint : CPoint(%d, %d)"), Model.getOriginalPoint().x, Model.getOriginalPoint().y);
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//NextPoint 확인
	text.Format(_T("NextPoint : CPoint(%d, %d)"), Model.getNextPoint().x, Model.getNextPoint().y);
	logList.emplace_back(text, CPoint(10, leftLine * 20), 1);
	leftLine++;

	//공백
	logList.emplace_back(L" ", CPoint(10, leftLine * 20), 1);
	leftLine++;

	return logList;
}