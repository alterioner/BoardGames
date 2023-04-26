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
			GridSpace[c][r].setItemIndex(CPoint(NONE, NONE));	//빈 공간으로 초기화
		}
	}

	getGridSpace()[1][2].setItemIndex(CPoint(SON, GREEN));		//녹색 子배치
	getGridSpace()[1][1].setItemIndex(CPoint(SON, RED));		//적색 子배치
	getGridSpace()[0][3].setItemIndex(CPoint(MINISTER, GREEN));	//녹색 相배치
	getGridSpace()[2][0].setItemIndex(CPoint(MINISTER, RED));	//적색 相배치
	getGridSpace()[2][3].setItemIndex(CPoint(GENERAL, GREEN));	//녹색 將배치
	getGridSpace()[0][0].setItemIndex(CPoint(GENERAL, RED));	//적색 將배치
	getGridSpace()[1][3].setItemIndex(CPoint(KING, GREEN));		//녹색 王배치
	getGridSpace()[1][0].setItemIndex(CPoint(KING, RED));		//적색 王배치
}

//격자판에 관련된 모든 정보 구현
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridRect = MakeGridRect(WinSize, GridSize, GridRectSize);		//격자판 생성
	GridSpace = MakeGridSpace(WinSize, GridSize, GridSpaceSize, false);	//격자판의 사용 공간 생성
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