#include "pch.h"
#include "TwelveModel.h"

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

//�����ǿ� ���õ� ��� ���� ����
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridRect = MakeGridRect(WinSize, GridSize, GridRectSize);		//������ ����
	GridSpace = MakeGridSpace(WinSize, GridSize, GridSpaceSize, false);	//�������� ��� ���� ����
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