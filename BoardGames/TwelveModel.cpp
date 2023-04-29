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

	/*
	CImage image;
	for (int i = 3; i < 4; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			CString imagePath;
			CString imageKey;
			
			imagePath = L"res/Twelve/G" + Item[i][j].getJob();
			imageKey = L"G" + Item[i][j].getJob();

			image.Load(imagePath + L".png");
			Item[i][j].insertSprite(imageKey, image);

			for (int index = 0; index < 8; index++)
			{
				CString num;
				image.Destroy();
				num.Format(_T("%d"), index);
				image.Load(imagePath + L"Move" + num + L".png");
				imageKey += L"Move" + num;
				Item[i][j].insertSprite(imageKey, image);
			}
		}
	}

	image.Destroy();
	image.Load(L"res/Twelve/GKing.png");
	Item[3][0].insertSprite(L"GKing", image);
	*/
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
			if (1)//Item[ActiveItemIndex.x][ActiveItemIndex.y].getSide() == Turn)	//���ʿ� �´� �������� Ȱ��ȭ�ߴ��� Ȯ��
			{
				if (Item[ActiveItemIndex.x][ActiveItemIndex.y].getPlace() == L"Catch") CurrentStatus = LOCATE;	//ĳġ������ ������ Ȱ��ȭ�� LOCATE ���·� �Ѿ
				else CurrentStatus = MOVE;
			}
		}
		break;
	case MOVE:
		if ((ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint)) != CPoint(NONE, NONE))		//���ڰ��� Ŭ�� �˻�� ���ÿ� Ŭ���� ���ڰ��� �ε��� ���� �� Ȱ��ȭ
		{
			OriginalPoint = Item[ActiveItemIndex.x][ActiveItemIndex.y].getPoint();
			if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))	//Ȱ��ȭ�� �������� Ȱ��ȭ�� ���ڰ������� �̵� �������� �˻�
			{
				int moveNcatch;			//0:�̵��Ұ�, 1:�̵����� + ��븻 ����, 2:�̵�����

				CPoint activeGridSpacesItemIndex = GridSpace[ActiveGridSpaceIndex.x][ActiveGridSpaceIndex.y].getItemIndex();

				NextPoint = GridSpace[ActiveGridSpaceIndex.x][ActiveGridSpaceIndex.y].getPoint();

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
				ChangeTurn();
				Animating = true;
			}
		}

		if (CurrentStatus == MOVE) CurrentStatus = NORMAL;
		break;
	case CATCH:
		CatchItem(CatchItemIndex);
		CurrentStatus = NORMAL;
		Animating = true;
		break;
	case LOCATE:
		ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint);

		if (ActiveGridSpaceIndex != CPoint(NONE, NONE))
		{
			LocateItem(ActiveItemIndex, ActiveGridSpaceIndex);
			ChangeTurn();
			Animating = true;
		}
		ActiveItemIndex = CPoint(NONE, NONE);
		CurrentStatus = NORMAL;
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
		if (AnimationFrame <= 7)
		{
			AnimationFrame++;
			return true;
		}
		else
		{
			AnimationFrame = 0;
			Animating = false;
			return false;
		}
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

//���� ����
void CTwelveModel::ChangeTurn()
{
	if (Turn == L"Green") Turn = L"Red";
	else Turn = L"Green";
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

//���� �������� ������ ���� ĳġ������ ����
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
	if (CatchSpace[side][itemIndex.x * 2].getItemIndex() == CPoint(NONE, NONE)) index = itemIndex.x * 2;	//�� ĳġ���� �ľ�
	else index = (itemIndex.x * 2) + 1;

	MoveItemInfo(itemIndex, CatchSpace[side][index].getPoint());
	Item[itemIndex.x][itemIndex.y].setPlace(L"Catch");
	CatchSpace[side][index].setItemIndex(itemIndex);
}

//�����ִ� �������� ���ڰ����� ��ġ
void CTwelveModel::LocateItem(CPoint itemIndex, CPoint gridSpaceIndex)
{
	if (GridSpace[gridSpaceIndex.x][gridSpaceIndex.y].getItemIndex() == CPoint(NONE, NONE))
	{
		int side;

		if (Item[itemIndex.x][itemIndex.y].getSide() == L"Green") side = GREEN;
		else side = RED;

		if ((side == GREEN && gridSpaceIndex.y != 0) || (side == RED && gridSpaceIndex.y != 3))	//��� ������ ���� ����
		{
			int catchIndex = itemIndex.x * 2;
			if (Item[itemIndex.x][itemIndex.y].getPoint() == CatchSpace[side][catchIndex].getPoint())	//�Ʒ��� ���� ���� ���� ��
			{

				CatchSpace[side][catchIndex].setItemIndex(CPoint(NONE, NONE));
				if (CatchSpace[side][catchIndex + 1].getItemIndex() != CPoint(NONE, NONE))	//ĳġ������ ù ���� ����� ��
				{
					ArrangeCatchSpace(side, catchIndex);
				}
			}
			else CatchSpace[side][catchIndex + 1].setItemIndex(CPoint(NONE, NONE));

			GridSpace[gridSpaceIndex.x][gridSpaceIndex.y].setItemIndex(itemIndex);
			MoveItemInfo(itemIndex, GridSpace[gridSpaceIndex.x][gridSpaceIndex.y].getPoint());
			Item[itemIndex.x][itemIndex.y].setPlace(L"Board");
		}
	}
}

//ĳġ���� ������
void CTwelveModel::ArrangeCatchSpace(int side, int index)
{
	CPoint ItemIndex = CatchSpace[side][index + 1].getItemIndex();

	CatchSpace[side][index].setItemIndex(ItemIndex);
	CatchSpace[side][index + 1].setItemIndex(CPoint(NONE, NONE));

	MoveItemInfo(ItemIndex, CatchSpace[side][index].getPoint());
}

//������ ����
bool CTwelveModel::MoveAnimation()
{
	CPoint movingPoint;				//���� �׷��� ��ġ
	CPoint move = OriginalPoint - NextPoint;

	switch (AnimationFrame)	//�����Ӻ� ������
	{
	case 0:	//0������
		movingPoint.x = OriginalPoint.x + (move.x * 0.5);		//�����ġ�� ������ġ�� �߰��� ��ġ
		movingPoint.y = OriginalPoint.y + (move.y * 0.5);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		AnimationFrame++;
		return true;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		movingPoint.x = NextPoint.x + (move.x * 0.8);			//�����ġ�� ������ġ�� 4/5�� ��ġ
		movingPoint.y = NextPoint.y + (move.y * 0.8);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		AnimationFrame++;
		return true;
		break;
	default:
		movingPoint = NextPoint;							//������ġ�� ��ġ
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		AnimationFrame = 0;
		ActiveItemIndex = CPoint(NONE, NONE);
		Animating = false;
		return false;
		break;
	}

}