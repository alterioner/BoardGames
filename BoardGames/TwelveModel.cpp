#include "pch.h"
#include "TwelveModel.h"

//격자판 구현
void CTwelveModel::MakeGridBoard(CPoint winSize)
{
	GridRect = MakeGridRect(winSize, GridSize, GridRectSize);			//격자칸 구현
	GridSpace = MakeGridSpace(winSize, GridSize, GridSpaceSize, false);	//격자공간 구현
}

//사용할 아이템 구현
void CTwelveModel::MakeItem()
{
	Item = new CItem * [4];

	for (int i = 0; i < 4; i++)
	{
		Item[i] = new CItem[2];
		Item[i][GREEN].setSide(L"Green");
		Item[i][RED].setSide(L"Red");
	}

	for (int i = 0; i < 2; i++)
	{
		Item[SON][i].setJob(L"Son");
		Item[MINISTER][i].setJob(L"Minister");
		Item[GENERAL][i].setJob(L"General");
		Item[KING][i].setJob(L"King");
	}
}

//캐치공간 구현
void CTwelveModel::MakeCatchSpace()
{
	CatchSpace = new CSpace * [2];

	CatchSpace[GREEN] = new CSpace[6];
	CatchSpace[GREEN][0].setPoint(CPoint(850, 600));
	CatchSpace[GREEN][1].setPoint(CPoint(850, 500));
	CatchSpace[GREEN][2].setPoint(CPoint(950, 600));
	CatchSpace[GREEN][3].setPoint(CPoint(950, 500));
	CatchSpace[GREEN][4].setPoint(CPoint(1050, 600));
	CatchSpace[GREEN][5].setPoint(CPoint(1050, 500));

	CatchSpace[RED] = new CSpace[6];
	CatchSpace[RED][0].setPoint(CPoint(350, 100));
	CatchSpace[RED][1].setPoint(CPoint(350, 200));
	CatchSpace[RED][2].setPoint(CPoint(250, 100));
	CatchSpace[RED][3].setPoint(CPoint(250, 200));
	CatchSpace[RED][4].setPoint(CPoint(150, 100));
	CatchSpace[RED][5].setPoint(CPoint(150, 200));

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			CatchSpace[i][j].setRect(PointToRect(CatchSpace[i][j].getPoint(), CPoint(100, 100)));
		}
	}
}

//격자판 정보 초기화
void CTwelveModel::ResetGridBoard()
{
	int col = GridSpaceSize.x;
	int row = GridSpaceSize.y;

	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			GridSpace[c][r].setItemIndex(CPoint(NONE, NONE));	//빈 공간으로 초기화
		}
	}

	GridSpace[1][2].setItemIndex(CPoint(SON, GREEN));		//녹색 子배치
	GridSpace[1][1].setItemIndex(CPoint(SON, RED));			//적색 子배치
	GridSpace[0][3].setItemIndex(CPoint(MINISTER, GREEN));	//녹색 相배치
	GridSpace[2][0].setItemIndex(CPoint(MINISTER, RED));	//적색 相배치
	GridSpace[2][3].setItemIndex(CPoint(GENERAL, GREEN));	//녹색 將배치
	GridSpace[0][0].setItemIndex(CPoint(GENERAL, RED));		//적색 將배치
	GridSpace[1][3].setItemIndex(CPoint(KING, GREEN));		//녹색 王배치
	GridSpace[1][0].setItemIndex(CPoint(KING, RED));		//적색 王배치
}

//아이템 정보 초기화
void CTwelveModel::ResetItem()
{
	//아이템 위치 초기화
	Item[SON][GREEN].setPoint(GridSpace[1][2].getPoint());
	Item[MINISTER][GREEN].setPoint(GridSpace[0][3].getPoint());
	Item[GENERAL][GREEN].setPoint(GridSpace[2][3].getPoint());
	Item[KING][GREEN].setPoint(GridSpace[1][3].getPoint());

	Item[SON][RED].setPoint(GridSpace[1][1].getPoint());
	Item[MINISTER][RED].setPoint(GridSpace[2][0].getPoint());
	Item[GENERAL][RED].setPoint(GridSpace[0][0].getPoint());
	Item[KING][RED].setPoint(GridSpace[1][0].getPoint());

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Item[i][j].setRect(PointToRect(Item[i][j].getPoint(), CPoint(90, 90)));	//아이템이 반응할 공간 초기화
			Item[i][j].setStatus(L"OnBoard");										//아이템이 속한 장소 초기화
		}
	}
}

//캐치공간 정보 초기화
void CTwelveModel::ResetCatchSpace()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			CatchSpace[i][j].setItemIndex(CPoint(NONE, NONE));
		}
	}
}

//기타 정보 초기화
void CTwelveModel::ResetStatus()
{
	//게임 상태 스택 초기화
	while (!GameStatusStack.empty()) GameStatusStack.pop();
	GameStatusStack.push(NORMAL);
	//승리 확인 조건 초기화
	Winer = NONE;
	KingInvasion = NONE;
	//기타 정보 초기화
	Turn = L"Green";
	Animating = false;
	AnimationFrame = -1;
	ActiveItemIndex = CPoint(NONE, NONE);
	ActiveGridSpaceIndex = CPoint(NONE, NONE);
	CatchItemIndex = CPoint(NONE, NONE);
	AnimatingItemIndex = CPoint(NONE, NONE);
	OriginalPoint = CPoint(NONE, NONE);
	NextPoint = CPoint(NONE, NONE);
}

void CTwelveModel::Game(CPoint clickPoint)
{
	if (GameStatusStack.top() == NORMAL)	//게임 상태가 NORMAL
	{
		if (ActiveItemIndex == CPoint(NONE, NONE))	//활성화된 아이템 없음
		{
			ActiveItemIndex = PointToItemIndex(clickPoint);
			if (ActiveItemIndex != CPoint(NONE, NONE))	//아이템이 클릭 됨
			{
				if (GetInstance(Item, ActiveItemIndex).getSide() != Turn)	//차례에 맞지 않은 아이템 클릭
				{
					ActiveItemIndex = CPoint(NONE, NONE);
				}
			}
		}
		else if (ActiveGridSpaceIndex == CPoint(NONE, NONE))	//활성화된 격자공간 없음
		{
			ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint);
			if (ActiveGridSpaceIndex != CPoint(NONE, NONE))		//격자공간이 클릭 됨
			{
				CPoint activeGridSpacesItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();
				if (activeGridSpacesItemIndex != CPoint(NONE, NONE))	//이동하려는 곳에 아이템 있음
				{
					if (GetInstance(Item, activeGridSpacesItemIndex).getSide() == Turn)	//목적지의 아이템이 같은 편
					{
						ActiveItemIndex = CPoint(NONE, NONE);
						ActiveGridSpaceIndex = CPoint(NONE, NONE);
					}
				}
			}
			else ActiveItemIndex = CPoint(NONE, NONE);	//격자공간이 클릭되지 않음
		}

		//MOVE와 LOCATE 구분
		if(ActiveItemIndex != CPoint(NONE, NONE) && ActiveGridSpaceIndex != CPoint(NONE, NONE))
		{
			if (GetInstance(Item, ActiveItemIndex).getStatus() == "OnBoard")
			{
				//이동 가능 여부 확인
				if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))
				{
					//아이템이 상대방 진영에 도착했을 시
					if ((Turn == L"Green" && ActiveGridSpaceIndex.y == 0) || (Turn == L"Red" && ActiveGridSpaceIndex.y == 3))
					{
						//아이템이 Son일 경우
						if (GetInstance(Item, ActiveItemIndex).getJob() == L"Son") GameStatusStack.push(REVERSE);
					}

					CatchItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();
					//잡힐 말이 있을 시
					if (CatchItemIndex != CPoint(NONE, NONE)) GameStatusStack.push(CATCH);
					GameStatusStack.push(MOVE);
				}
				else
				{
					ActiveItemIndex = CPoint(NONE, NONE);
					ActiveGridSpaceIndex = CPoint(NONE, NONE);
					CatchItemIndex = CPoint(NONE, NONE);
				}
			}
			else if (GetInstance(Item, ActiveItemIndex).getStatus() == "OnCatch")
			{
				//이동 가능 여부 확인
				if (CheckCanLocate(ActiveGridSpaceIndex)) GameStatusStack.push(LOCATE);
				else
				{
					ActiveItemIndex = CPoint(NONE, NONE);
					ActiveGridSpaceIndex = CPoint(NONE, NONE);
				}
			}
		}
	}
	
	if (GameStatusStack.top() != NORMAL)
	{
		switch (GameStatusStack.top())
		{
		case MOVE:
			MoveSpaceInfo(PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, ActiveItemIndex).getPoint()), ActiveGridSpaceIndex);
			MoveItemInfo(ActiveItemIndex, GetInstance(GridSpace, ActiveGridSpaceIndex).getPoint());
			break;
		case CATCH:
			CatchItem(CatchItemIndex);
			break;
		case REVERSE:
			Item[ActiveItemIndex.x][ActiveItemIndex.y].setJob(L"Lord");
			break;
		case LOCATE:
			LocateItem(ActiveItemIndex, ActiveGridSpaceIndex);
			break;
		}
		Animating = true;
	}
}

//클릭 좌표를 받아 해당 좌표의 아이템 인덱스 반환
CPoint CTwelveModel::PointToItemIndex(CPoint clickPoint)
{
	for (int job = 0; job < 4; job++)
	{
		for (int side = 0; side < 2; side++)
		{
			if (PtInRect(Item[job][side].getRect(), clickPoint)) return CPoint(job, side);
		}
	}

	return CPoint(NONE, NONE);
}

//차례 변경
void CTwelveModel::ChangeTurn()
{
	if (Turn == L"Green") Turn = L"Red";
	else Turn = L"Green";
}

//아이템 배치시 적절한 공간을 선택하였는지 검사
bool CTwelveModel::CheckCanLocate(CPoint gridSpaceIndex)
{
	if (GetInstance(GridSpace, gridSpaceIndex).getItemIndex() == CPoint(NONE, NONE))
	{
		if ((Turn == L"Green" && gridSpaceIndex.y != 0) || (Turn == L"Red" && gridSpaceIndex.y != 3))
		{
			return true;
		}
	}
	return false;
}

//각 아이템의 이동하려는 방향과 이동할 수 있는 방향이 일치하는지 검사
bool CTwelveModel::CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, itemIndex).getPoint());
	CString job = GetInstance(Item, itemIndex).getJob();	//종류별 움직임 확인 구분

	if (job == L"Minister") return MoveDiagonal(itemsGridSpaceIndex, gridSpaceIndex);
	else if (job == L"General") return MoveStraight(itemsGridSpaceIndex, gridSpaceIndex);
	else if (job == L"King") return (MoveDiagonal(itemsGridSpaceIndex, gridSpaceIndex) || MoveStraight(itemsGridSpaceIndex, gridSpaceIndex));
	else if (job == L"Son") return MoveSon(itemIndex, itemsGridSpaceIndex, gridSpaceIndex);
	else if (job == L"Lord") return MoveLord(itemIndex, itemsGridSpaceIndex, gridSpaceIndex);

	return false;
}

bool CTwelveModel::MoveDiagonal(CPoint originalIndex, CPoint nextIndex)
{
	if (originalIndex.x - 1 == nextIndex.x || originalIndex.x + 1 == nextIndex.x)
	{
		if (originalIndex.y - 1 == nextIndex.y || originalIndex.y + 1 == nextIndex.y)
		{
			return true;
		}
	}

	return false;
}

bool CTwelveModel::MoveStraight(CPoint originalIndex, CPoint nextIndex)
{
	if (originalIndex.x == nextIndex.x)
	{
		if (originalIndex.y - 1 == nextIndex.y || originalIndex.y + 1 == nextIndex.y)
		{
			return true;
		}
	}
	else if (originalIndex.y == nextIndex.y)
	{
		if (originalIndex.x - 1 == nextIndex.x || originalIndex.x + 1 == nextIndex.x)
		{
			return true;
		}
	}

	return false;
}

bool CTwelveModel::MoveSon(CPoint itemIndex, CPoint originalIndex, CPoint nextIndex)
{
	if (GetInstance(Item, itemIndex).getSide() == L"Green" && !(nextIndex.y < originalIndex.y)) return false;
	else if (GetInstance(Item, itemIndex).getSide() == L"Red" && !(nextIndex.y > originalIndex.y)) return false;

	return MoveStraight(originalIndex, nextIndex);
}

bool CTwelveModel::MoveLord(CPoint itemIndex, CPoint originalIndex, CPoint nextIndex)
{
	if (MoveDiagonal(originalIndex, nextIndex))
	{
		if (GetInstance(Item, itemIndex).getSide() == L"Green" && nextIndex.y > originalIndex.y) return false;
		else if (GetInstance(Item, itemIndex).getSide() == L"Red" && nextIndex.y < originalIndex.y) return false;
		else return true;
	}
	else return MoveStraight(originalIndex, nextIndex);
}

//출발지 격자공간 인덱스와 도착지 격자공간 인덱스를 입력받아 각 격자공간의 아이템 인덱스 정보 갱신
void CTwelveModel::MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex)
{
	CPoint itemIndex = GetInstance(GridSpace, originalIndex).getItemIndex();
	GridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	GridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}

//이동할 아이템 인덱스와 이동할 포인트를 입력받아 아이템 정보를 갱신
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint nextPoint)
{
	AnimatingItemIndex = itemIndex;
	OriginalPoint = GetInstance(Item, itemIndex).getPoint();
	NextPoint = nextPoint;
	Item[itemIndex.x][itemIndex.y].setPoint(nextPoint);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(nextPoint, CPoint(90, 90)));
}

//잡힌 아이템의 직업에 따라 캐치공간에 정렬
void CTwelveModel::CatchItem(CPoint itemIndex)
{
	AnimatingItemIndex = itemIndex;
	int side;
	if (GetInstance(Item, itemIndex).getSide() == L"Green") {
		Item[itemIndex.x][itemIndex.y].setSide(L"Red");
		side = RED;
	}
	else
	{
		Item[itemIndex.x][itemIndex.y].setSide(L"Green");
		side = GREEN;
	}

	if (GetInstance(Item, itemIndex).getJob() == L"Lord") Item[itemIndex.x][itemIndex.y].setJob(L"Son");

	int index;
	if (CatchSpace[side][itemIndex.x * 2].getItemIndex() == CPoint(NONE, NONE)) index = itemIndex.x * 2;	//빈 캐치공간 파악
	else index = (itemIndex.x * 2) + 1;

	MoveItemInfo(itemIndex, CatchSpace[side][index].getPoint());
	CatchSpace[side][index].setItemIndex(itemIndex);
}

//잡혀있는 아이템을 격자공간에 배치
void CTwelveModel::LocateItem(CPoint itemIndex, CPoint gridSpaceIndex)
{
	AnimatingItemIndex = itemIndex;
	if (GetInstance(GridSpace, gridSpaceIndex).getItemIndex() == CPoint(NONE, NONE))
	{
		int side;

		if (GetInstance(Item, itemIndex).getSide() == L"Green") side = GREEN;
		else side = RED;

		int catchIndex = itemIndex.x * 2;
		if (GetInstance(Item, itemIndex).getPoint() == CatchSpace[side][catchIndex].getPoint())	//아래의 잡힌 말을 꺼낼 때
		{
			CatchSpace[side][catchIndex].setItemIndex(CPoint(NONE, NONE));
			if (CatchSpace[side][catchIndex + 1].getItemIndex() != CPoint(NONE, NONE))	//캐치공간의 첫 열이 비었을 때
			{
				ArrangeCatchSpace(side, catchIndex);
			}
		}
		else CatchSpace[side][catchIndex + 1].setItemIndex(CPoint(NONE, NONE));

		GridSpace[gridSpaceIndex.x][gridSpaceIndex.y].setItemIndex(itemIndex);
		MoveItemInfo(itemIndex, GetInstance(GridSpace, gridSpaceIndex).getPoint());
		Item[itemIndex.x][itemIndex.y].setStatus(L"OnBoard");
	}
}

//캐치공간 재정렬
void CTwelveModel::ArrangeCatchSpace(int side, int index)
{
	CPoint ItemIndex = CatchSpace[side][index + 1].getItemIndex();

	CatchSpace[side][index].setItemIndex(ItemIndex);
	CatchSpace[side][index + 1].setItemIndex(CPoint(NONE, NONE));

	MoveItemInfo(ItemIndex, CatchSpace[side][index].getPoint());
}

//애니메이션 및 애니메이션 종료시 정보 초기화
bool CTwelveModel::Animation()
{
	switch (GameStatusStack.top())
	{
	case MOVE:
	case LOCATE:
		MoveAnimation();
		break;
	case CATCH:
		CatchAnimation();
		break;
	case REVERSE:
		AnimatingItemIndex = ActiveItemIndex;
		ReverseAnimation();
		break;
	}

	if (GameStatusStack.top() != NORMAL) return true;
	else
	{
		ActiveItemIndex = CPoint(NONE, NONE);
		ActiveGridSpaceIndex = CPoint(NONE, NONE);
		CatchItemIndex = CPoint(NONE, NONE);
		AnimatingItemIndex = CPoint(NONE, NONE);
		OriginalPoint = CPoint(NONE, NONE);
		NextPoint = CPoint(NONE, NONE);
		ChangeTurn();
		return false;
	}
}

//Move 애니메이션 구현
void CTwelveModel::MoveAnimation()
{
	CString status;
	CPoint movingPoint;	//말이 그려질 위치
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;

	status.Format(_T("Move%d"), AnimationFrame);	//프레임별 이미지
	switch (AnimationFrame)	//프레임별 위치
	{
	case 0:
		movingPoint.x = OriginalPoint.x + (move.x * 0.5);		//출발위치와 도착위치의 중간에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.5);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		break;
	case 1:
		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.8);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		break;
	case 2:
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(NextPoint);
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		break;
	default:
		status = L"OnBoard";
		AnimationFrame = -1;
		GameStatusStack.pop();
		Animating = false;
		break;
	}
	Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(status);
}

//Catch 애니메이션 구현
void CTwelveModel::CatchAnimation()
{
	CString status;
	CPoint movingPoint;	//말이 그려질 위치
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;

	status.Format(_T("Catch%d"), AnimationFrame);
	switch (AnimationFrame)
	{
	case 0:

		movingPoint.x = OriginalPoint.x + (move.x * 0.4);		//출발위치와 도착위치의 중간에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.4);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
	case 1:
		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.8);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
		
	case 2:
		movingPoint.x = OriginalPoint.x + (move.x * 0.9);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.9);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
	case 3:
		if (GetInstance(Item, CatchItemIndex).getSide() == L"Green")	//죽은 말이 녹색측으로 갔다면
		{
			movingPoint.x = NextPoint.x - 10;					//도착위치에서 살짝 떨어진 곳에 위치
			movingPoint.y = NextPoint.y - 10;
		}
		else if (GetInstance(Item, CatchItemIndex).getSide() == L"Red")	//죽은 말이 적색측으로 갔다면
		{
			movingPoint.x = NextPoint.x + 10;
			movingPoint.y = NextPoint.y + 10;
		}
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
	case 4:
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(NextPoint);
	case 5:
	case 6:
		break;
	default:
		status = L"OnCatch";
		AnimationFrame = -1;
		GameStatusStack.pop();
		Animating = false;
		break;
	}
	Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(status);
}

//Reverse 애니메이션 구현
void CTwelveModel::ReverseAnimation()
{
	CString str;
	AnimationFrame++;
	str.Format(_T("Reverse%d"), AnimationFrame);

	if (AnimationFrame < 16) Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(str);
	else
	{
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(L"OnBoard");
		AnimationFrame = -1;
		GameStatusStack.pop();
		Animating = false;
	}
}