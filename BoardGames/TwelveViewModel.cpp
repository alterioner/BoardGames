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
	MoveItemIndex = CPoint(NONE, NONE);
	if (!Model.getAnimating())
	{
		Model.Game(clickPoint);
		if (Model.getAnimating()) return Model.Animation();
		else return false;
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

	CPoint lastItemIndex = Model.getAnimatingItemIndex();
	int lastImageIndex;

	if (lastItemIndex != CPoint(NONE, NONE)) lastImageIndex = lastItemIndex.x * 2 + lastItemIndex.y;
	else lastImageIndex = NONE;

	for (int job = 0; job < 4; job++)
	{
		for (int side = 0; side < 2; side++)
		{
			filePath[job * 2 + side] = L"res/Twelve/" + item[job][side].getSide() + item[job][side].getJob() + item[job][side].getStatus() + L".png";	//파일 경로 설정

			imagePoint[job * 2 + side] = item[job][side].getPoint();
		}
	}

	if (lastImageIndex != NONE)
	{
		for (int i = lastImageIndex; i < 7; i++)
		{
			CString tempString = filePath[i];
			filePath[i] = filePath[i + 1];
			filePath[i + 1] = tempString;

			CPoint tempPoint = imagePoint[i];
			imagePoint[i] = imagePoint[i + 1];
			imagePoint[i + 1] = tempPoint;
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
	int extra = 12;

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
	CPoint origin = Model.getActiveItemIndex();
	CPoint next = Model.getActiveGridSpaceIndex();
	log[12].setPoint(CPoint(1180, 0));
	if (Model.getActiveItemIndex() != CPoint(NONE, NONE))
	{
		//text.Format(_T("Item : CPoint(%d, %d), GridSpace : CPoint(%d, %d)"), Model.getItem()[origin.x][origin.y].getPoint().x, Model.getItem()[origin.x][origin.y].getPoint().y, Model.getGridSpace()[next.x][next.y].getPoint().x, Model.getGridSpace()[next.x][next.y].getPoint().y);
		text = Model.getItem()[Model.getActiveItemIndex().x][Model.getActiveItemIndex().y].getStatus();
	}
	else if (Model.getCatchItemIndex() != CPoint(NONE, NONE))
	{
		text = Model.getItem()[Model.getCatchItemIndex().x][Model.getCatchItemIndex().y].getStatus();
	}
	else {
		text.Format(_T("뭐"));
	}
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

	//GameStatus 확인
	log[15].setPoint(CPoint(10, 40));
	text.Format(_T("GameStatusQueue : %d"), Model.getGameStatusQueue());
	log[15].setText(text);
	log[15].setAlign(1);

	//활성화된 아이템 인덱스 확인
	log[16].setPoint(CPoint(10, 60));
	if ((point = Model.getActiveItemIndex()) == CPoint(NONE, NONE)) log[16].setText(L"Active Item Index : NONE");
	else
	{
		text.Format(_T("Active Item Index : CPoint(%d, %d)"), point.x, point.y);
		log[16].setText(text);
	}
	log[16].setAlign(1);

	//활성화된 격자판의 인덱스 확인
	log[17].setPoint(CPoint(10, 80));
	if ((point = Model.getActiveGridSpaceIndex()) == CPoint(NONE, NONE)) log[17].setText(L"Active Grid Index : NONE");
	else
	{
		text.Format(_T("Active Grid Index : CPoint(%d, %d)"), point.x, point.y);
		log[17].setText(text);
	}
	log[17].setAlign(1);

	//잡히는 아이템 인덱스 확인
	log[18].setPoint(CPoint(10, 100));
	if ((point = Model.getCatchItemIndex()) == CPoint(NONE, NONE)) log[18].setText(L"Catch Item Index : NONE");
	else
	{
		text.Format(_T("Catch Item Index : CPoint(%d, %d)"), point.x, point.y);
		log[18].setText(text);
	}
	log[18].setAlign(1);

	//AnimationFrame 확인
	log[19].setPoint(CPoint(10, 120));
	text.Format(_T("AnimationFrame : %d"), Model.getAnimationFrame());
	log[19].setText(text);
	log[19].setAlign(1);

	//OriginalPoint 확인
	log[20].setPoint(CPoint(10, 140));
	text.Format(_T("OriginalPoint : CPoint(%d, %d)"), Model.getOriginalPoint().x, Model.getOriginalPoint().y);
	log[20].setText(text);
	log[20].setAlign(1);

	//NextPoint 확인
	log[21].setPoint(CPoint(10, 160));
	text.Format(_T("NextPoint : CPoint(%d, %d)"), Model.getNextPoint().x, Model.getNextPoint().y);
	log[21].setText(text);
	log[21].setAlign(1);

	//Turn 확인
	log[22].setPoint(CPoint(10, 180));
	log[22].setText(L"Turn : " + Model.getTurn());
	log[22].setAlign(1);

	//Turn 확인
	log[23].setPoint(CPoint(10, 200));
	log[23].setText(L"Turn : ");// + Model.getTurn());
	log[23].setAlign(1);

	return std::make_tuple(log, col * row + extra);
}