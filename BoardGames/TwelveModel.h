#pragma once
#include "GridBoardTool.h"

#define NONE 15

#define GREEN 0
#define RED 1

#define SON 0
#define MINISTER 1
#define	GENERAL 2
#define	KING 3

#define NORMAL 0
#define MOVE 1
#define CATCH 2
#define LOCATE 3

class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//한 칸 크기
	CPoint GridRectSize = CPoint(3, 4);		//격자판 크기
	CRect** GridRect;						//격자판을 그릴 사각형
	CPoint GridSpaceSize = CPoint(3, 4);	//격자판의 사용 공간 크기
	CSpace** GridSpace;						//격자판의 사용 공간 정보
	CItem** Item;							//아이템 정보

	int currentStatus = NORMAL;	//현재 상태 기록
	CPoint activeItemIndex = CPoint(NONE, NONE);		//활성화된 아이템 인덱스
	CPoint activeGridSpaceIndex = CPoint(NONE, NONE);	//활성화된 격자판 인덱스
public:
	static CTwelveModel& getInstance() {
		static CTwelveModel instance;
		return instance;
	}
	CTwelveModel(CTwelveModel const&) = delete;
	void operator=(CTwelveModel const&) = delete;

	CPoint getGridSize() { return GridSize; }
	void setGridSize(CPoint GridSize) { this->GridSize = GridSize; }
	CPoint getGridRectSize() { return GridRectSize; }
	void setGridRectSize(CPoint GridRectSize) { this->GridRectSize = GridRectSize; }
	CRect** getGridRect() { return GridRect; }
	void setGridRect(CRect** GridRect) { this->GridRect = GridRect; }
	CPoint getGridSpaceSize() { return GridSpaceSize; }
	void setGridSpaceSize(CPoint GridSpaceSize) { this->GridSpaceSize = GridSpaceSize; }
	CSpace** getGridSpace() { return GridSpace; }
	void setGridSpace(CSpace** GridSpace) { this->GridSpace = GridSpace; }
	CItem** getItem() { return Item; }
	void setItem(CItem** Item) { this->Item = Item; }

	int getCurrentStatus() { return currentStatus; }
	CPoint getActiveItemIndex() { return activeItemIndex; }
	CPoint getActiveGridSpaceIndex() { return activeGridSpaceIndex; }

	void MakeGridBoard(CPoint winSize);	//격자판 구현
	void ResetGridBoard();				//격자판 정보 초기화

	void MakeItem();	//아이템 구현
	void ResetItem();	//아이템 정보 초기화

	void Game(CPoint clickPoint);

	CPoint PointToItemIndex(CPoint clickPoint);		//아이템 활성화

	bool CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex);	//이동 가능 여부 확인
	bool MoveSon(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveDiagonal(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveStraight(CPoint itemIndex, CPoint gridSpaceIndex);

	void MoveItemInfo(CPoint itemIndex, CPoint moveTo);			//아이템 정보 이동
};

