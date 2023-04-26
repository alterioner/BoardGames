#include "pch.h"
#include "TwelveModel.h"

//������ ����
void CTwelveModel::MakeGridBoard(CPoint winSize)
{
	GridRect = MakeGridRect(winSize, GridSize, GridRectSize);			//����ĭ ����
	GridSpace = MakeGridSpace(winSize, GridSize, GridSpaceSize, false);	//���ڰ��� ����
}

//����� ������ ����
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

//ĳġ���� ����
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

//������ ���� �ʱ�ȭ
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

//������ ���� �ʱ�ȭ
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

//ĳġ���� ���� �ʱ�ȭ
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
		if ((ActiveItemIndex = PointToItemIndex(clickPoint)) != CPoint(NONE, NONE))		//������ Ŭ�� �˻�� ���ÿ� Ŭ���� ������ �ε��� ���� �� Ȱ��ȭ
		{
			if (Item[ActiveItemIndex.x][ActiveItemIndex.y].getPlace() == L"Catch") CurrentStatus = LOCATE;
			else CurrentStatus = MOVE;
		}
		break;
	case MOVE:
		if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))		//���ڰ��� Ŭ�� �˻�� ���ÿ� Ŭ���� ���ڰ��� �ε��� ���� �� Ȱ��ȭ
		{
			if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))	//Ȱ��ȭ�� �������� Ȱ��ȭ�� ���ڰ������� �̵� �������� �˻�
			{
				int moveNcatch;			//0:�̵��Ұ�, 1:�̵����� + ��븻 ����, 2:�̵�����

				CPoint activeGridSpacesItemIndex = GridSpace[ActiveGridSpaceIndex.x][ActiveGridSpaceIndex.y].getItemIndex();

				if (activeGridSpacesItemIndex == CPoint(NONE, NONE)) moveNcatch = 2;																						//�������� ������ ����
				else if (Item[ActiveItemIndex.x][ActiveItemIndex.y].getSide() != Item[activeGridSpacesItemIndex.x][activeGridSpacesItemIndex.y].getSide()) moveNcatch = 1;	//�������� �������� ����
				else moveNcatch = 0;																																		//�������� �������� �Ʊ�

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

//����� ���ڰ��� �ε����� ������ ���ڰ��� �ε����� �Է¹޾� �� ���ڰ����� ������ �ε��� ���� ����
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


//���� ���� ������ ���� ĳġ ������ ������
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