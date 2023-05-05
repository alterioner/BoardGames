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
#define CATCH 2
#define REVERSE 3
#define LOCATE 4

class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//����ĭ ����
	CPoint GridRectSize = CPoint(3, 4);		//����ĭ ũ��
	CRect** GridRect;						//����ĭ�� �׸� �簢��
	CPoint GridSpaceSize = CPoint(3, 4);	//���ڰ��� ũ��
	CSpace** GridSpace;						//���ڰ��� ����
	CItem** Item;							//������ ����
	CSpace** CatchSpace;					//ĳġ���� ����

	CString Turn = L"Green";			//����
	std::stack<int> GameStatusStack;	//���� ����

	CPoint ActiveItemIndex = CPoint(NONE, NONE);		//Ȱ��ȭ�� ������ �ε���
	CPoint ActiveGridSpaceIndex = CPoint(NONE, NONE);	//Ȱ��ȭ�� ���ڰ��� �ε���
	CPoint CatchItemIndex = CPoint(NONE, NONE);			//���� ������ �ε���

	CPoint AnimatingItemIndex = CPoint(NONE, NONE);	//�ִϸ��̼��� ����ǰ� �ִ� ������ �ε���
	bool Animating = false;		//�ִϸ��̼� ���
	int AnimationFrame = -1;	//�ִϸ��̼� ������ ������ ����
	CPoint OriginalPoint;		//�ִϸ��̼� ���� �� ������ ��� ����
	CPoint NextPoint;			//�ִϸ��̼� ���� �� ������ ���� ����

	bool GameEnd = false;
	CString Winner;	//�̱� ��
	CString KingInvasion;	//ŷ�� ħ���� ��Ȳ
public:
	//Model ����� �������� ����
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

	bool getGameEnd() { return GameEnd; }
	CString getWinner() { return Winner; }
	CString getKingInvasion() { return KingInvasion; }

	void MakeGridBoard(CPoint winSize);	//������ ����
	void MakeItem();					//������ ����
	void MakeCatchSpace();				//ĳġ���� ����

	void ResetGridBoard();	//������ ���� �ʱ�ȭ
	void ResetItem();		//������ ���� �ʱ�ȭ
	void ResetCatchSpace();	//ĳġ���� ���� �ʱ�ȭ
	void ResetStatus();		//��Ÿ ���� �ʱ�ȭ

	void Game(CPoint clickPoint);

	CPoint PointToItemIndex(CPoint clickPoint);		//��ǥ�� ������ �ε����� ��ȯ

	void ChangeTurn();	//���� ����

	bool CheckCanLocate(CPoint gridSpaceIndex);						//��ġ ���� ���� Ȯ��
	bool CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex);		//�̵� ���� ���� Ȯ��
	bool MoveDiagonal(CPoint originalIndex, CPoint nextIndex);
	bool MoveStraight(CPoint originalIndex, CPoint nextIndex);
	bool MoveSon(CPoint itemIndex, CPoint originalIndex, CPoint nextIndex);
	bool MoveLord(CPoint itemIndex, CPoint originalIndex, CPoint nextIndex);

	void MoveItemInfo(CPoint itemIndex, CPoint moveTo);			//������ ���� �̵�
	void MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex);	//���ڰ����� ������ �ε��� ���� �̵�
	void CatchItem(CPoint itemIndex);							//���� ������ ���� �̵�
	void LocateItem(CPoint itemIndex, CPoint gridIndex);		//���� ������ ���ġ
	void ArrangeCatchSpace(int side, int index);				//ĳġ���� ����

	bool Animation();		//�ִϸ��̼� ����
	void MoveAnimation();
	void CatchAnimation();
	void ReverseAnimation();
};

