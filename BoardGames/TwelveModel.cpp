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
			Item[i][j].setPlace(L"Board");											//아이템이 속한 장소 초기화
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
	switch (CurrentStatus)
	{
	case NORMAL:
		if ((ActiveItemIndex = PointToItemIndex(clickPoint)) != CPoint(NONE, NONE))		//아이템 클릭 검사와 동시에 클릭한 아이템 인덱스 저장 및 활성화
		{
			if (Item[ActiveItemIndex.x][ActiveItemIndex.y].getPlace() == L"Catch") CurrentStatus = LOCATE;
			else CurrentStatus = MOVE;
		}
		break;
	case MOVE:
		if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))		//격자공간 클릭 검사와 동시에 클릭한 격자공간 인덱스 저장 및 활성화
		{
			if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))	//활성화된 아이템이 활성화된 격자공간으로 이동 가능한지 검사
			{
				int moveNcatch;			//0:이동불가, 1:이동가능 + 상대말 잡음, 2:이동가능

				CPoint activeGridSpacesItemIndex = GridSpace[ActiveGridSpaceIndex.x][ActiveGridSpaceIndex.y].getItemIndex();

				if (activeGridSpacesItemIndex == CPoint(NONE, NONE)) moveNcatch = 2;																						//목적지에 아이템 없음
				else if (Item[ActiveItemIndex.x][ActiveItemIndex.y].getSide() != Item[activeGridSpacesItemIndex.x][activeGridSpacesItemIndex.y].getSide()) moveNcatch = 1;	//목적지의 아이템이 적군
				else moveNcatch = 0;																																		//목적지의 아이템이 아군

				switch (moveNcatch)
				{
				case 1:
					CatchItemIndex = activeGridSpacesItemIndex;
					CurrentStatus = CATCH;
				case 2:
					MoveSpaceInfo(PointToGridSpaceIndex(GridSpace, GridSpaceSize, Item[ActiveItemIndex.x][ActiveItemIndex.y].getPoint()), ActiveGridSpaceIndex);
					CPoint activeSpacePoint = GridSpace[ActiveGridSpaceIndex.x][ActiveGridSpaceIndex.y].getPoint();
					MoveItemInfo(ActiveItemIndex, activeSpacePoint);
				}
				Animating = true;
			}
		}

		ActiveItemIndex = CPoint(NONE, NONE);
		if (CurrentStatus == MOVE) CurrentStatus = NORMAL;
		break;
	case CATCH:
		CatchItem(CatchItemIndex);
		CurrentStatus = NORMAL;
		Animating = true;
		break;
	}
}

bool CTwelveModel::Animation()
{
	if (CurrentStatus == CATCH)
	{
		Animating = false;
		return true;
	}
	else
	{
		Animating = false;
		return false;
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

//각 말의 이동하려는 방향과 이동할 수 있는 방향이 일치하는지 검사
bool CTwelveModel::CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CString job = Item[itemIndex.x][itemIndex.y].getJob();
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

	if (Item[itemIndex.x][itemIndex.y].getSide() == L"Green") itemsGridIndex.y--;
	else itemsGridIndex.y++;

	if (itemsGridIndex == gridSpaceIndex) return true;
	else return false;
}

bool CTwelveModel::MoveDiagonal(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, Item[itemIndex.x][itemIndex.y].getPoint());

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
	CPoint itemsGridIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, Item[itemIndex.x][itemIndex.y].getPoint());

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
	CPoint itemIndex = GridSpace[originalIndex.x][originalIndex.y].getItemIndex();
	GridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	GridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}

//이동할 아이템 인덱스와 이동할 포인트를 입력받아 아이템 정보를 갱신
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint moveTo)
{
	Item[itemIndex.x][itemIndex.y].setPoint(moveTo);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(moveTo, CPoint(90, 90)));
}


//잡힌 말의 직업에 따라 캐치 공간에 정렬함
void CTwelveModel::CatchItem(CPoint itemIndex)
{
	int side;
	if (Item[itemIndex.x][itemIndex.y].getSide() == L"Green") {
		Item[itemIndex.x][itemIndex.y].setSide(L"Red");
		side = RED;
	}
	else
	{
		Item[itemIndex.x][itemIndex.y].setSide(L"Green");
		side = GREEN;
	}

	int index;
	if (CatchSpace[side][itemIndex.x * 2].getItemIndex() == CPoint(NONE, NONE)) index = itemIndex.x * 2;
	else index = (itemIndex.x * 2) + 1;

	MoveItemInfo(itemIndex, CatchSpace[side][index].getPoint());
	CatchSpace[side][index].setItemIndex(itemIndex);
	Item[itemIndex.x][itemIndex.y].setPlace(L"Catch");
}