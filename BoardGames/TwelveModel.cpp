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
			Item[i][j].setStatus(L"OnBoard");										//�������� ���� ��� �ʱ�ȭ
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

//��Ÿ ���� �ʱ�ȭ
void CTwelveModel::ResetStatus()
{
	//���� ���� ���� �ʱ�ȭ
	while (!GameStatusStack.empty()) GameStatusStack.pop();
	GameStatusStack.push(NORMAL);
	//�¸� Ȯ�� ���� �ʱ�ȭ
	Winer = NONE;
	KingInvasion = NONE;
	//��Ÿ ���� �ʱ�ȭ
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
	if (GameStatusStack.top() == NORMAL)	//���� ���°� NORMAL
	{
		if (ActiveItemIndex == CPoint(NONE, NONE))	//Ȱ��ȭ�� ������ ����
		{
			ActiveItemIndex = PointToItemIndex(clickPoint);
			if (ActiveItemIndex != CPoint(NONE, NONE))	//�������� Ŭ�� ��
			{
				if (GetInstance(Item, ActiveItemIndex).getSide() != Turn)	//���ʿ� ���� ���� ������ Ŭ��
				{
					ActiveItemIndex = CPoint(NONE, NONE);
				}
			}
		}
		else if (ActiveGridSpaceIndex == CPoint(NONE, NONE))	//Ȱ��ȭ�� ���ڰ��� ����
		{
			ActiveGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, clickPoint);
			if (ActiveGridSpaceIndex != CPoint(NONE, NONE))		//���ڰ����� Ŭ�� ��
			{
				CPoint activeGridSpacesItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();
				if (activeGridSpacesItemIndex != CPoint(NONE, NONE))	//�̵��Ϸ��� ���� ������ ����
				{
					if (GetInstance(Item, activeGridSpacesItemIndex).getSide() == Turn)	//�������� �������� ���� ��
					{
						ActiveItemIndex = CPoint(NONE, NONE);
						ActiveGridSpaceIndex = CPoint(NONE, NONE);
					}
				}
			}
			else ActiveItemIndex = CPoint(NONE, NONE);	//���ڰ����� Ŭ������ ����
		}

		//MOVE�� LOCATE ����
		if(ActiveItemIndex != CPoint(NONE, NONE) && ActiveGridSpaceIndex != CPoint(NONE, NONE))
		{
			if (GetInstance(Item, ActiveItemIndex).getStatus() == "OnBoard")
			{
				//�̵� ���� ���� Ȯ��
				if (CheckCanMove(ActiveItemIndex, ActiveGridSpaceIndex))
				{
					//�������� ���� ������ �������� ��
					if ((Turn == L"Green" && ActiveGridSpaceIndex.y == 0) || (Turn == L"Red" && ActiveGridSpaceIndex.y == 3))
					{
						//�������� Son�� ���
						if (GetInstance(Item, ActiveItemIndex).getJob() == L"Son") GameStatusStack.push(REVERSE);
					}

					CatchItemIndex = GetInstance(GridSpace, ActiveGridSpaceIndex).getItemIndex();
					//���� ���� ���� ��
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
				//�̵� ���� ���� Ȯ��
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

//������ ��ġ�� ������ ������ �����Ͽ����� �˻�
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

//�� �������� �̵��Ϸ��� ����� �̵��� �� �ִ� ������ ��ġ�ϴ��� �˻�
bool CTwelveModel::CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex)
{
	CPoint itemsGridSpaceIndex = PointToGridSpaceIndex(GridSpace, GridSpaceSize, GetInstance(Item, itemIndex).getPoint());
	CString job = GetInstance(Item, itemIndex).getJob();	//������ ������ Ȯ�� ����

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

//����� ���ڰ��� �ε����� ������ ���ڰ��� �ε����� �Է¹޾� �� ���ڰ����� ������ �ε��� ���� ����
void CTwelveModel::MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex)
{
	CPoint itemIndex = GetInstance(GridSpace, originalIndex).getItemIndex();
	GridSpace[nextIndex.x][nextIndex.y].setItemIndex(itemIndex);
	GridSpace[originalIndex.x][originalIndex.y].setItemIndex(CPoint(NONE, NONE));
}

//�̵��� ������ �ε����� �̵��� ����Ʈ�� �Է¹޾� ������ ������ ����
void CTwelveModel::MoveItemInfo(CPoint itemIndex, CPoint nextPoint)
{
	AnimatingItemIndex = itemIndex;
	OriginalPoint = GetInstance(Item, itemIndex).getPoint();
	NextPoint = nextPoint;
	Item[itemIndex.x][itemIndex.y].setPoint(nextPoint);
	Item[itemIndex.x][itemIndex.y].setRect(PointToRect(nextPoint, CPoint(90, 90)));
}

//���� �������� ������ ���� ĳġ������ ����
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
	if (CatchSpace[side][itemIndex.x * 2].getItemIndex() == CPoint(NONE, NONE)) index = itemIndex.x * 2;	//�� ĳġ���� �ľ�
	else index = (itemIndex.x * 2) + 1;

	MoveItemInfo(itemIndex, CatchSpace[side][index].getPoint());
	CatchSpace[side][index].setItemIndex(itemIndex);
}

//�����ִ� �������� ���ڰ����� ��ġ
void CTwelveModel::LocateItem(CPoint itemIndex, CPoint gridSpaceIndex)
{
	AnimatingItemIndex = itemIndex;
	if (GetInstance(GridSpace, gridSpaceIndex).getItemIndex() == CPoint(NONE, NONE))
	{
		int side;

		if (GetInstance(Item, itemIndex).getSide() == L"Green") side = GREEN;
		else side = RED;

		int catchIndex = itemIndex.x * 2;
		if (GetInstance(Item, itemIndex).getPoint() == CatchSpace[side][catchIndex].getPoint())	//�Ʒ��� ���� ���� ���� ��
		{
			CatchSpace[side][catchIndex].setItemIndex(CPoint(NONE, NONE));
			if (CatchSpace[side][catchIndex + 1].getItemIndex() != CPoint(NONE, NONE))	//ĳġ������ ù ���� ����� ��
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

//ĳġ���� ������
void CTwelveModel::ArrangeCatchSpace(int side, int index)
{
	CPoint ItemIndex = CatchSpace[side][index + 1].getItemIndex();

	CatchSpace[side][index].setItemIndex(ItemIndex);
	CatchSpace[side][index + 1].setItemIndex(CPoint(NONE, NONE));

	MoveItemInfo(ItemIndex, CatchSpace[side][index].getPoint());
}

//�ִϸ��̼� �� �ִϸ��̼� ����� ���� �ʱ�ȭ
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

//Move �ִϸ��̼� ����
void CTwelveModel::MoveAnimation()
{
	CString status;
	CPoint movingPoint;	//���� �׷��� ��ġ
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;

	status.Format(_T("Move%d"), AnimationFrame);	//�����Ӻ� �̹���
	switch (AnimationFrame)	//�����Ӻ� ��ġ
	{
	case 0:
		movingPoint.x = OriginalPoint.x + (move.x * 0.5);		//�����ġ�� ������ġ�� �߰��� ��ġ
		movingPoint.y = OriginalPoint.y + (move.y * 0.5);
		Item[ActiveItemIndex.x][ActiveItemIndex.y].setPoint(movingPoint);
		break;
	case 1:
		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//�����ġ�� ������ġ�� 4/5�� ��ġ
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

//Catch �ִϸ��̼� ����
void CTwelveModel::CatchAnimation()
{
	CString status;
	CPoint movingPoint;	//���� �׷��� ��ġ
	CPoint move = NextPoint - OriginalPoint;
	AnimationFrame++;

	status.Format(_T("Catch%d"), AnimationFrame);
	switch (AnimationFrame)
	{
	case 0:

		movingPoint.x = OriginalPoint.x + (move.x * 0.4);		//�����ġ�� ������ġ�� �߰��� ��ġ
		movingPoint.y = OriginalPoint.y + (move.y * 0.4);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
	case 1:
		movingPoint.x = OriginalPoint.x + (move.x * 0.8);			//�����ġ�� ������ġ�� 4/5�� ��ġ
		movingPoint.y = OriginalPoint.y + (move.y * 0.8);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
		
	case 2:
		movingPoint.x = OriginalPoint.x + (move.x * 0.9);			//�����ġ�� ������ġ�� 4/5�� ��ġ
		movingPoint.y = OriginalPoint.y + (move.y * 0.9);
		Item[CatchItemIndex.x][CatchItemIndex.y].setPoint(movingPoint);
		break;
	case 3:
		if (GetInstance(Item, CatchItemIndex).getSide() == L"Green")	//���� ���� ��������� ���ٸ�
		{
			movingPoint.x = NextPoint.x - 10;					//������ġ���� ��¦ ������ ���� ��ġ
			movingPoint.y = NextPoint.y - 10;
		}
		else if (GetInstance(Item, CatchItemIndex).getSide() == L"Red")	//���� ���� ���������� ���ٸ�
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

//Reverse �ִϸ��̼� ����
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