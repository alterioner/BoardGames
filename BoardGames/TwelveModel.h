#pragma once
#include "GridBoardTool.h"
class CTwelveModel : public CGridBoardTool
{
	CPoint GridSize;		//�� ĭ ũ��
	CPoint GridBoardSize;	//������ ũ��
	CRect** GridBoardRect;	//������ �׸� �� ���̴� �簢��
public:
	CPoint getGridSize() { return GridSize; }
	void setGridSize(CPoint GridSize) { this->GridSize = GridSize; }
	CPoint getGridBoardSize() { return GridBoardSize; }
	void setGridBoardSize(CPoint GridBoardSize) { this->GridBoardSize = GridBoardSize; }
	CRect** getGridBoardRect() { return GridBoardRect; }
	void setGridBoardRect(CRect** GridBoardRect) { this->GridBoardRect = GridBoardRect; }

	void MakeGridBoard(CPoint WinSize);	//������ �����
};

