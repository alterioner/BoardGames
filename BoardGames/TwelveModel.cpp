#include "pch.h"
#include "TwelveModel.h"

//격자판 구현
void CTwelveModel::MakeGridBoard(CPoint winSize)
{
	GridRect = MakeGridRect(winSize, GridSize, GridRectSize);			//격자칸 구현
	GridSpace = MakeGridSpace(winSize, GridSize, GridSpaceSize, false);	//격자공간 구현
	GameStatusQueue.push(NORMAL);
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

void CTwelveModel::Game(CPoint clickPoint)
{
	if (GameStatusQueue.top() == NORMAL)
	{
		if (ActiveItemIndex == CPoint(NONE, NONE))
		{
			if ((ActiveItemIndex = PointToItemIndex(clickPoint)) != CPoint(NONE, NONE))		//아이템 클릭 검사와 동시에 클릭한 아이템 인덱스 저장 및 활성화
			{
				if (1)//GetInstance(Item, ActiveItemIndex).getSide() == Turn)	//차례에 맞는 아이템을 활성화했는지 확인
				{
					//if (GetInstance(Item, ActiveItemIndex).getStatus() == L"OnCatch") GameStatusQueue.push(LOCATE);
					//else GameStatusQueue.push(MOVE);
				}
			}
		}
		else
		{
			bool canDo = false;
			if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))
			{
				CPoint activeGridSpacesItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();

				if (GetInstance(Item, ActiveItemIndex).getStatus() == L"OnBoard")
				{
					if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))
					{

						if (activeGridSpacesItemIndex == CPoint(NONE, NONE)) canDo = true;
						else
						{
							if (GetInstance(Item, ActiveItemIndex).getSide() != GetInstance(Item, activeGridSpacesItemIndex).getSide())
							{
								CatchItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();
								GameStatusQueue.push(CATCH);
								canDo = true;
							}
						}

						if (canDo) GameStatusQueue.push(MOVE);
					}
				}
				else if (GetInstance(Item, ActiveItemIndex).getStatus() == L"OnCatch")
				{
					if (activeGridSpacesItemIndex == CPoint(NONE, NONE))
					{
						int side;
						if (GetInstance(Item, ActiveItemIndex).getSide() == L"Green") side = GREEN;
						else side = RED;

						if ((side == GREEN && ActiveGridSpaceIndex.y != 0) || (side == RED && ActiveGridSpaceIndex.y != 3))	//상대 구역에 놓지 못함
						{
							GameStatusQueue.push(LOCATE);
							canDo = true;
						}
					}
				}
			}

			if (!canDo) ActiveItemIndex = CPoint(NONE, NONE);
		}
	}
	
	if (GameStatusQueue.top() != NORMAL)
	{
		switch (GameStatusQueue.top())
		{
			/*
		case NORMAL:
			if (ActiveItemIndex == CPoint(NONE, NONE))
			{
				if ((ActiveItemIndex = PointToItemIndex(clickPoint)) != CPoint(NONE, NONE))		//아이템 클릭 검사와 동시에 클릭한 아이템 인덱스 저장 및 활성화
				{
					if (1)//GetInstance(Item, ActiveItemIndex).getSide() == Turn)	//차례에 맞는 아이템을 활성화했는지 확인
					{
						//if (GetInstance(Item, ActiveItemIndex).getStatus() == L"OnCatch") GameStatusQueue.push(LOCATE);
						//else GameStatusQueue.push(MOVE);
					}
				}
			}
			else
			{
				bool canDo = false;
				if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))
				{
					if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))
					{
						bool isOnBoard;
						if (GetInstance(Item, ActiveItemIndex).getStatus() == L"OnBoard") isOnBoard = true;
						else isOnBoard = false;

						CPoint activeGridSpacesItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();

						if (activeGridSpacesItemIndex == CPoint(NONE, NONE)) canDo = true;
						else
						{
							if (isOnBoard == true && GetInstance(Item, ActiveItemIndex).getSide() != GetInstance(Item, activeGridSpacesItemIndex).getSide()) canDo = true;
						}

						if (canDo)
						{
							if (isOnBoard) GameStatusQueue.push(MOVE);
							else GameStatusQueue.push(LOCATE);
						}
					}
				}

				if(!canDo) ActiveItemIndex = CPoint(NONE, NONE);
			}
			break;
			*/
		case MOVE:
			/*
			if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))		//격자공간 클릭 검사와 동시에 클릭한 격자공간 인덱스 저장 및 활성화
			{
				if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))	//활성화된 아이템이 활성화된 격자공간으로 이동 가능한지 검사
				{
					int moveNcatch;			//0:이동불가, 1:이동가능 + 상대말 잡음, 2:이동가능

					CPoint activeGridSpacesItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();

					if (activeGridSpacesItemIndex == CPoint(NONE, NONE)) moveNcatch = 2;																//목적지에 아이템 없음
					else if (GetInstance(Item, ActiveItemIndex).getSide() != GetInstance(Item, activeGridSpacesItemIndex).getSide()) moveNcatch = 1;	//목적지의 아이템이 적군
					else moveNcatch = 0;																												//목적지의 아이템이 아군

					switch (moveNcatch)
					{
					case 1:
						CatchItemIndex = activeGridSpacesItemIndex;
						GameStatusQueue.push(CATCH);
					case 2:
						MoveSpaceInfo(PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, ActiveItemIndex).getPoint()), ActiveGridSpaceIndex);
						CPoint activeSpacePoint = GetInstance(GridSpace, ActiveGridSpaceIndex).getPoint();
						MoveItemInfo(ActiveItemIndex, activeSpacePoint);
						ChangeTurn();
						Animating = true;
					}
					ChangeTurn();
					GameStatusQueue.push(MOVE);
					Animating = true;
				}
			}
			*/
				MoveSpaceInfo(PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, ActiveItemIndex).getPoint()), ActiveGridSpaceIndex);
				MoveItemInfo(ActiveItemIndex, GetInstance(GridSpace, ActiveGridSpaceIndex).getPoint());
				ChangeTurn();
				Animating = true;
			break;
		case CATCH:
			CatchItem(CatchItemIndex);
			Animating = true;
			break;
		case LOCATE:
			/*
			ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint);		//클릭한 격자판의 인덱스 저장

			if (ActiveGridSpaceIndex != CPoint(NONE, NONE))											//격자판이 클릭되었는지 확인
			{
				if (GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex() == CPoint(NONE, NONE))	//격자판이 비어있는지 확인
				{
					int side;
					if (GetInstance(Item, ActiveItemIndex).getSide() == L"Green") side = GREEN;
					else side = RED;

					if ((side == GREEN && ActiveGridSpaceIndex.y != 0) || (side == RED && ActiveGridSpaceIndex.y != 3))	//상대 구역에 놓지 못함
					{
						LocateItem(ActiveItemIndex, ActiveGridSpaceIndex);
						ChangeTurn();
						GameStatusQueue.push(MOVE);
						Animating = true;
					}
				}
			}
			*/
			LocateItem(ActiveItemIndex, ActiveGridSpaceIndex);
			ChangeTurn();
			Animating = true;
		}
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

//각 말의 이동하려는 방향과 이동할 수 있는 방향이 일치하는지 검사
bool CTwelveModel::CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint nextItemIndex;
	if ((nextItemIndex = GetInstance(GridSpace, gridSpaceIndex).getItemIndex()) != CPoint(NONE, NONE))	//이동하려는 자리가 비었는지 확인
	{
		if (GetInstance(Item, itemIndex).getSide() == GetInstance(Item, nextItemIndex).getSide()) return false;	//이동하려는 자리의 아이템이 같은 편인지 확인
	}
	CString job = GetInstance(Item, itemIndex).getJob();
	if (job == L"Son") return MoveSon(itemIndex, gridSpaceIndex);
	else if (job == L"Minister") return MoveDiagonal(itemIndex, gridSpaceIndex);
	else if (job == L"General") return MoveStraight(itemIndex, gridSpaceIndex);
	else if (job == L"King") return (MoveDiagonal(itemIndex, gridSpaceIndex) || MoveStraight(itemIndex, gridSpaceIndex));

	return false;
}

//子 아이템 이동
bool CTwelveModel::MoveSon(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, Item[itemIndex.x][itemIndex.y].getPoint());

	if (GetInstance(Item, itemIndex).getSide() == L"Green") itemsGridIndex.y--;
	else itemsGridIndex.y++;

	if (itemsGridIndex == gridSpaceIndex) return true;
	else return false;
}

bool CTwelveModel::MoveDiagonal(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, itemIndex).getPoint());

	if (itemsGridIndex.x - 1 == gridSpaceIndex.x || itemsGridIndex.x + 1 == gridSpaceIndex.x)
	{
		if (itemsGridIndex.y - 1 == gridSpaceIndex.y || itemsGridIndex.y + 1 == gridSpaceIndex.y)
		{
			return true;
		}
	}

	return false;
}

bool CTwelveModel::MoveStraight(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, itemIndex).getPoint());

	if (itemsGridIndex.x == gridSpaceIndex.x)
	{
		if (itemsGridIndex.y - 1 == gridSpaceIndex.y || itemsGridIndex.y + 1 == gridSpaceIndex.y)
		{
			return true;
		}
	}
	else if (itemsGridIndex.y == gridSpaceIndex.y)
	{
		if (itemsGridIndex.x - 1 == gridSpaceIndex.x || itemsGridIndex.x + 1 == gridSpaceIndex.x)
		{
			return true;
		}
	}

	return false;
}

//출발지 격자공간 인덱스와 도착지 격자공간 인덱스를 입력받아 각 격자공간의 아이템 인덱스 정보 갱신
void CTwelveModel::MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex)
{
	CPoint itemIndex = GetInstance(GridSpace, originalIndex).getItemIndex();
	GridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	GridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}

//이동할 아이템 인덱스와 이동할 포인트를 입력받아 아이템 정보를 갱신
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint moveTo)
{
	AnimatingItemIndex = itemIndex;
	OriginalPoint = GetInstance(Item, itemIndex).getPoint();
	NextPoint = moveTo;
	Item[itemIndex.x][itemIndex.y].setPoint(moveTo);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(moveTo, CPoint(90, 90)));
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

//애니메이션
bool CTwelveModel::Animation()
{
	bool temp;
	if (GameStatusQueue.top() == CATCH)
	{
		return CatchAnimation();
	}
	else if (GameStatusQueue.top() == MOVE || GameStatusQueue.top() == LOCATE)
	{
		temp = MoveAnimation();
		if (!temp)
		{
			if (GameStatusQueue.top() == CATCH) return true;
			else return false;
		}
		else return true;
	}
}

//Move 애니메이션 구현
bool CTwelveModel::MoveAnimation()
{
	CString str;
	CPoint movingPoint;				//말이 그려질 위치
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;
	
	switch (AnimationFrame)	//프레임별 움직임
	{
	case 0:	//0프레임
		str.Format(_T("Move%d"), AnimationFrame);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(str);

		movingPoint.x = OriginalPoint.x + (move.x * 0.5);		//출발위치와 도착위치의 중간에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.5);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		return true;
		break;
	case 1:
		str.Format(_T("Move%d"), AnimationFrame);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(str);

		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.8);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		return true;
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		str.Format(_T("Move%d"), AnimationFrame);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(str);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(NextPoint);
		return true;
		break;
	default:
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setStatus(L"OnBoard");
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(NextPoint);
		AnimationFrame = -1;
		ActiveItemIndex = CPoint(NONE, NONE);
		ActiveGridSpaceIndex = CPoint(NONE, NONE);
		AnimatingItemIndex = CPoint(NONE, NONE);
		Animating = false;
		GameStatusQueue.pop();
		return false;
		break;
	}	
}

//Catch 애니메이션 구현
bool CTwelveModel::CatchAnimation()
{
	CString str;
	CPoint movingPoint;				//말이 그려질 위치
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;

	switch (AnimationFrame)	//프레임별 움직임
	{
	case 0:	//0프레임
		str.Format(_T("Catch%d"), AnimationFrame);
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(str);

		movingPoint.x = OriginalPoint.x + (move.x * 0.4);		//출발위치와 도착위치의 중간에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.4);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		return true;
		break;
	case 1:
		str.Format(_T("Catch%d"), AnimationFrame);
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(str);

		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.8);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		return true;
		break;
		
	case 2:
		str.Format(_T("Catch%d"), AnimationFrame);
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(str);

		movingPoint.x = OriginalPoint.x + (move.x * 0.9);			//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = OriginalPoint.y + (move.y * 0.9);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		return true;
		break;
	case 3:
		str.Format(_T("Catch%d"), AnimationFrame);
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(str);
		if (Item[CatchItemIndex.x][CatchItemIndex.y].getSide() == L"Green")			//죽은 말이 녹색측으로 갔다면
		{
			movingPoint.x = NextPoint.x - 10;					//도착위치에서 살짝 떨어진 곳에 위치
			movingPoint.y = NextPoint.y - 10;
		}
		else if (Item[CatchItemIndex.x][CatchItemIndex.y].getSide() == L"Red")			//죽은 말이 적색측으로 갔다면
		{
			movingPoint.x = NextPoint.x + 10;					//도착위치에서 살짝 떨어진 곳에 위치
			movingPoint.y = NextPoint.y + 10;
		}
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		return true;
		break;
	case 4:
	case 5:
	case 6:
		str.Format(_T("Catch%d"), AnimationFrame);
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(str);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(NextPoint);
		return true;
		break;
	default:
		Item[CatchItemIndex.x][CatchItemIndex.y].setStatus(L"OnCatch");
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(NextPoint);
		AnimationFrame = -1;
		CatchItemIndex = CPoint(NONE, NONE);
		Animating = false;
		GameStatus = NORMAL;
		AnimatingItemIndex = CPoint(NONE, NONE);
		GameStatusQueue.pop();
		return false;
		break;
	}
}