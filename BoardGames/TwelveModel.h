#pragma once
#include "GridBoardTool.h"
class CTwelveModel : public CGridBoardTool
{
	CPoint GridSize = CPoint(100, 100);		//�� ĭ ũ��
	CPoint GridBoardSize = CPoint(3, 4);	//������ ũ��
	CRect** GridBoardRect;					//������ �׸� �� ���̴� �簢��
	CGameTool::CSpace** GridBoard;			//������ ����
public:
	CPoint getGridSize() { return GridSize; }
	void setGridSize(CPoint GridSize) { this->GridSize = GridSize; }
	CPoint getGridBoardSize() { return GridBoardSize; }
	void setGridBoardSize(CPoint GridBoardSize) { this->GridBoardSize = GridBoardSize; }
	CRect** getGridBoardRect() { return GridBoardRect; }
	void setGridBoardRect(CRect** GridBoardRect) { this->GridBoardRect = GridBoardRect; }

	void MakeGridBoard(CPoint WinSize);	//������ �����
};

