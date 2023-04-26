#include "pch.h"
#include "TwelveModel.h"

//�����ǿ� ���õ� ��� ���� ����
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridRect = MakeGridRect(WinSize, GridSize, GridRectSize);		//������ ����
	GridSpace = MakeGridSpace(WinSize, GridSize, GridSpaceSize, false);	//�������� ��� ���� ����
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

	getGridSpace()[1][2].setItemIndex(CPoint(SON, GREEN));		//��� ��ġ
	getGridSpace()[1][1].setItemIndex(CPoint(SON, RED));		//���� ��ġ
	getGridSpace()[0][3].setItemIndex(CPoint(MINISTER, GREEN));	//��� �ӹ�ġ
	getGridSpace()[2][0].setItemIndex(CPoint(MINISTER, RED));	//���� �ӹ�ġ
	getGridSpace()[2][3].setItemIndex(CPoint(GENERAL, GREEN));	//��� ���ġ
	getGridSpace()[0][0].setItemIndex(CPoint(GENERAL, RED));	//���� ���ġ
	getGridSpace()[1][3].setItemIndex(CPoint(KING, GREEN));		//��� �ݹ�ġ
	getGridSpace()[1][0].setItemIndex(CPoint(KING, RED));		//���� �ݹ�ġ
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
		if ((activeItemIndex = ActiveItemIndex(clickPoint)) != CPoint(NONE, NONE))
		{
			if (Item[activeItemIndex.x][activeItemIndex.y].getPlace() == L"Catch") currentStatus = LOCATE;
			else currentStatus = MOVE;
		}
		break;
	case MOVE:
		if ((activeGridSpaceIndex = ActiveGridSpaceIndex(clickPoint)) != CPoint(NONE, NONE))
		{
			CPoint gridItemIndex = GridSpace[activeGridSpaceIndex.x][activeGridSpaceIndex.y].getItemIndex();
			CPoint activeSpacePoint = GridSpace[activeGridSpaceIndex.x][activeGridSpaceIndex.y].getPoint();

			MoveSpaceInfo(ActiveGridSpaceIndex(Item[activeItemIndex.x][activeItemIndex.y].getPoint()), activeGridSpaceIndex);
			MoveItemInfo(activeItemIndex, activeSpacePoint);
		}

		activeItemIndex = CPoint(NONE, NONE);
		currentStatus = NORMAL;
		break;
	}
}

//��ǥ�� �޾� �ش� ��ǥ�� ����ĭ �ε��� ��ȯ
CPoint CTwelveModel::ActiveGridSpaceIndex(CPoint clickPoint)
{
	int col = GridSpaceSize.x;
	int row = GridSpaceSize.y;

	for (int c = 0; c < col; c++)
	{
		for (int r = 0; r < row; r++)
		{
			if (PtInRect(GridSpace[c][r].getRect(), clickPoint)) return CPoint(c, r);
		}
	}

	return CPoint(NONE, NONE);
}

//Ŭ�� ��ǥ�� �޾� �ش� ��ǥ�� ������ �ε��� ��ȯ
CPoint CTwelveModel::ActiveItemIndex(CPoint clickPoint)
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

//����� ����ĭ �ε����� ������ ����ĭ �ε����� �Է¹޾� ����ĭ ������ ����
void CTwelveModel::MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex)
{
	CPoint itemIndex = GridSpace[originalIndex.x][originalIndex.y].getItemIndex();
	GridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	GridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}


//�̵��� ������ �ε����� �̵��� ����Ʈ�� �Է¹޾� ������ ������ ����
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint moveTo)
{
	Item[itemIndex.x][itemIndex.y].setPoint(moveTo);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(moveTo, CPoint(90, 90)));
}