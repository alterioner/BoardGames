#include "pch.h"
#include "TwelveModel.h"

//�����ǿ� ���õ� ��� ���� ����
void CTwelveModel::MakeGridBoard(CPoint winSize)
{
	GridRect = MakeGridRect(winSize, GridSize, GridRectSize);		//������ ����
	GridSpace = MakeGridSpace(winSize, GridSize, GridSpaceSize, false);	//�������� ��� ���� ����
}

void CTwelveModel::ResetGridBoard()
{
	int col = GridSpaceSize.x;
	int row = GridSpaceSize.y;

	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			GridSpace[c][r].setItemIndex(CPoint(NONE, NONE));	//�� �������� �ʱ�ȭ
		}
	}

	GridSpace[1][2].setItemIndex(CPoint(SON, GREEN));		//��� ��ġ
	GridSpace[1][1].setItemIndex(CPoint(SON, RED));			//���� ��ġ
	GridSpace[0][3].setItemIndex(CPoint(MINISTER, GREEN));	//��� �ӹ�ġ
	GridSpace[2][0].setItemIndex(CPoint(MINISTER, RED));	//���� �ӹ�ġ
	GridSpace[2][3].setItemIndex(CPoint(GENERAL, GREEN));	//��� ���ġ
	GridSpace[0][0].setItemIndex(CPoint(GENERAL, RED));		//���� ���ġ
	GridSpace[1][3].setItemIndex(CPoint(KING, GREEN));		//��� �ݹ�ġ
	GridSpace[1][0].setItemIndex(CPoint(KING, RED));		//���� �ݹ�ġ
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

//�������� ��ġ�� �ʱ�ȭ�Ѵ� (CTwelveModel)
void CTwelveModel::ResetItem()
{
	//������ ��ġ �ʱ�ȭ
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
			Item[i][j].setRect(PointToRect(Item[i][j].getPoint(), CPoint(90, 90)));	//�������� ������ ���� �ʱ�ȭ
			Item[i][j].setPlace(L"Board");											//�������� ���� ��� �ʱ�ȭ
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

//Ŭ�� ��ǥ�� �޾� �ش� ��ǥ�� ������ �ε��� ��ȯ
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

//�̵��� ������ �ε����� �̵��� ����Ʈ�� �Է¹޾� ������ ������ ����
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint moveTo)
{
	Item[itemIndex.x][itemIndex.y].setPoint(moveTo);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(moveTo, CPoint(90, 90)));
}

//�� ���� �̵��Ϸ��� ����� �̵��� �� �ִ� ������ ��ġ�ϴ��� �˻�
bool CTwelveModel::CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CString job = Item[itemIndex.x][itemIndex.y].getJob();
	if (job == L"Son") return MoveSon(itemIndex, gridSpaceIndex);
	else if (job == L"Minister") return MoveDiagonal(itemIndex, gridSpaceIndex);
	else if (job == L"General") return MoveStraight(itemIndex, gridSpaceIndex);
	else if (job == L"King") return (MoveDiagonal(itemIndex, gridSpaceIndex) || MoveStraight(itemIndex, gridSpaceIndex));

	return false;
}

//� ������ �̵�
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