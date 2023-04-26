#pragma once
#include "GridBoardTool.h"

#define NONE 15

#define GREEN 0
#define RED 1

#define SON 0
#define MINISTER 1
#define	GENERAL 2
#define	KING 3

class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//�� ĭ ũ��
	CPoint GridRectSize = CPoint(3, 4);		//������ ũ��
	CRect** GridRect;						//�������� �׸� �簢��
	CPoint GridSpaceSize = CPoint(3, 4);	//�������� ��� ���� ũ��
	CSpace** GridSpace;						//�������� ��� ���� ����
	CItem** Item;							//������ ����
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

	void MakeGridBoard(CPoint WinSize);	//������ ����
	void ResetGridBoard();				//������ ���� �ʱ�ȭ

	void MakeItem();	//������ ����
	void ResetItem();	//������ ���� �ʱ�ȭ
};

