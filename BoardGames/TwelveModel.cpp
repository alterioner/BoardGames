#include "pch.h"
#include "TwelveModel.h"

//격자판에 관련된 모든 정보 구현
void CTwelveModel::MakeGridBoard(CPoint winSize)
{
	GridRect = MakeGridRect(winSize, GridSize, GridRectSize);		//격자판 생성
	GridSpace = MakeGridSpace(winSize, GridSize, GridSpaceSize, false);	//격자판의 사용 공간 생성
}

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

//아이템의 위치를 초기화한다 (CTwelveModel)
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

void CTwelveModel::Game(CPoint clickPoint)
{
	switch (currentStatus)
	{
	case NORMAL:
		if ((activeItemIndex = PointToItemIndex(clickPoint)) != CPoint(NONE, NONE))
		{
			if (Item[activeItemIndex.x][activeItemIndex.y].getPlace() == L"Catch") currentStatus = LOCATE;
			else currentStatus = MOVE;
		}
		break;
	case MOVE:
		if ((activeGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))
		{
			if (CheckCanMove(activeItemIndex, activeGridSpaceIndex))
			{
				CPoint gridItemIndex = GridSpace[activeGridSpaceIndex.x][activeGridSpaceIndex.y].getItemIndex();
				CPoint activeSpacePoint = GridSpace[activeGridSpaceIndex.x][activeGridSpaceIndex.y].getPoint();

				MoveSpaceInfo(GridSpace, PointToGridSpaceIndex(GridSpace, GridSpaceSize, Item[activeItemIndex.x][activeItemIndex.y].getPoint()), activeGridSpaceIndex);
				MoveItemInfo(activeItemIndex, activeSpacePoint);
			}
		}

		activeItemIndex = CPoint(NONE, NONE);
		currentStatus = NORMAL;
		break;
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

//이동할 아이템 인덱스와 이동할 포인트를 입력받아 아이템 정보를 갱신
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint moveTo)
{
	Item[itemIndex.x][itemIndex.y].setPoint(moveTo);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(moveTo, CPoint(90, 90)));
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