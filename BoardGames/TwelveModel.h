#pragma once
#include "GridBoardTool.h"
#include <stack>

#define NONE 15

#define GREEN 0
#define RED 1

#define SON 0
#define MINISTER 1
#define	GENERAL 2
#define	KING 3

#define NORMAL 0
#define MOVE 1
#define CATCH 3
#define REVERSE 4
#define LOCATE 5

class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//격자칸 넓이
	CPoint GridRectSize = CPoint(3, 4);		//격자칸 크기
	CRect** GridRect;						//격자칸을 그릴 사각형
	CPoint GridSpaceSize = CPoint(3, 4);	//격자공간 크기
	CSpace** GridSpace;						//격자공간 정보
	CItem** Item;							//아이템 정보
	CSpace** CatchSpace;					//캐치공간 정보

	CString Turn = L"Green";	//차례
	std::stack<int> GameStatusStack;

	CPoint ActiveItemIndex = CPoint(NONE, NONE);		//활성화된 아이템 인덱스
	CPoint ActiveGridSpaceIndex = CPoint(NONE, NONE);	//활성화된 격자공간 인덱스
	CPoint CatchItemIndex = CPoint(NONE, NONE);			//잡힌 아이템 인덱스

	CPoint AnimatingItemIndex = CPoint(NONE, NONE);	//애니메이션이 적용되고 있는 아이템 인덱스
	bool Animating = false;			//애니메이션 토글
	int AnimationFrame = -1;		//애니메이션 구현시 프레임 구분
	CPoint OriginalPoint;		//애니메이션 구현 시 아이템 출발 지점
	CPoint NextPoint;			//애니메이션 구현 시 아이템 도착 지점

	int Winer;	//이긴 편
	int KingInvasion;	//킹이 이길 상황
public:
	static CTwelveModel& getInstance() {
		static CTwelveModel instance;
		return instance;
	}
	CTwelveModel(CTwelveModel const&) = delete;
	void operator=(CTwelveModel const&) = delete;

	CPoint getGridSize() { return GridSize; }
	CPoint getGridRectSize() { return GridRectSize; }
	CRect** getGridRect() { return GridRect; }
	CPoint getGridSpaceSize() { return GridSpaceSize; }
	CSpace** getGridSpace() { return GridSpace; }
	CItem** getItem() { return Item; }

	CString getTurn() { return Turn; }
	int getGameStatusQueue() { return GameStatusStack.top(); }

	CPoint getActiveItemIndex() { return ActiveItemIndex; }
	CPoint getActiveGridSpaceIndex() { return ActiveGridSpaceIndex; }
	CPoint getCatchItemIndex() { return CatchItemIndex; }

	CPoint getAnimatingItemIndex() { return AnimatingItemIndex; }
	bool getAnimating() { return Animating; }
	int getAnimationFrame() { return AnimationFrame; }
	CPoint getOriginalPoint() { return OriginalPoint; }
	CPoint getNextPoint() { return NextPoint; }

	int getKingInvasion() { return KingInvasion; }

	void MakeGridBoard(CPoint winSize);	//격자판 구현
	void MakeItem();					//아이템 구현
	void MakeCatchSpace();				//캐치공간 구현

	void ResetGridBoard();	//격자판 정보 초기화
	void ResetItem();		//아이템 정보 초기화
	void ResetCatchSpace();	//캐치공간 정보 초기화

	CPoint temp;

	void Game(CPoint clickPoint);

	CPoint PointToItemIndex(CPoint clickPoint);		//좌표를 아이템 인덱스로 변환

	void ChangeTurn();

	bool CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex);	//역할상 이동 가능 여부 확인
	bool MoveSon(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveDiagonal(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveStraight(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveLord(CPoint itemIndex, CPoint gridSpaceIndex);

	void MoveItemInfo(CPoint itemIndex, CPoint moveTo);			//아이템 정보 이동
	void MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex);	//격자공간의 아이템 인덱스 정보 이동
	void CatchItem(CPoint itemIndex);							//잡힌 아이템 정보 이동
	void LocateItem(CPoint itemIndex, CPoint gridIndex);		//잡힌 아이템 재배치
	void ArrangeCatchSpace(int side, int index);				//캐치공간 정렬

	bool Animation();
	void MoveAnimation();
	bool CatchAnimation();
	void ReverseAnimation();
};

