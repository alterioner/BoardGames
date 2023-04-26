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
	CPoint GridSize = CPoint (100, 100);	//����ĭ ����
	CPoint GridRectSize = CPoint(3, 4);		//����ĭ ũ��
	CRect** GridRect;						//����ĭ�� �׸� �簢��
	CPoint GridSpaceSize = CPoint(3, 4);	//���ڰ��� ũ��
	CSpace** GridSpace;						//���ڰ��� ����
	CItem** Item;							//������ ����
	CSpace** CatchSpace;					//ĳġ���� ����

	bool Animating = false;
	int CurrentStatus = NORMAL;	//���� ���� ���
	CPoint ActiveItemIndex = CPoint(NONE, NONE);		//Ȱ��ȭ�� ������ �ε���
	CPoint ActiveGridSpaceIndex = CPoint(NONE, NONE);	//Ȱ��ȭ�� ���ڰ��� �ε���
	CPoint CatchItemIndex = CPoint(NONE, NONE);			//���� ������ �ε���
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

	bool getAnimating() { return Animating; }
	int getCurrentStatus() { return CurrentStatus; }
	CPoint getActiveItemIndex() { return ActiveItemIndex; }
	CPoint getActiveGridSpaceIndex() { return ActiveGridSpaceIndex; }

	void MakeGridBoard(CPoint winSize);	//������ ����
	void MakeItem();					//������ ����
	void MakeCatchSpace();				//ĳġ���� ����

	void ResetGridBoard();	//������ ���� �ʱ�ȭ
	void ResetItem();		//������ ���� �ʱ�ȭ
	void ResetCatchSpace();	//ĳġ���� ���� �ʱ�ȭ

	CPoint temp;

	void Game(CPoint clickPoint);
	bool Animation();

	CPoint PointToItemIndex(CPoint clickPoint);		//��ǥ�� ������ �ε����� ��ȯ

	bool CheckCanMove(CPoint itemIndex, CPoint gridSpaceIndex);	//�̵� ���� ���� Ȯ��
	bool MoveSon(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveDiagonal(CPoint itemIndex, CPoint gridSpaceIndex);
	bool MoveStraight(CPoint itemIndex, CPoint gridSpaceIndex);

	void MoveItemInfo(CPoint itemIndex, CPoint moveTo);			//������ ���� �̵�
	void MoveSpaceInfo(CPoint originalIndex, CPoint nextIndex);	//���ڰ����� ������ �ε��� ���� �̵�
	void CatchItem(CPoint itemIndex);							//���� ������ ���� �̵�		
};

