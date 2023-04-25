#pragma once
#include "GridBoardTool.h"
class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//�� ĭ ũ��
	CPoint GridBoardSize = CPoint(3, 4);	//������ ũ��
	CRect** GridBoardRect;					//�������� �׸� �簢��
	CSpace** GridBoard;						//�������� ��� ���� ����
public:
	static CTwelveModel& getInstance() {
		static CTwelveModel instance;
		return instance;
	}
	CTwelveModel(CTwelveModel const&) = delete;
	void operator=(CTwelveModel const&) = delete;

	CPoint getGridSize() { return GridSize; }
	void setGridSize(CPoint GridSize) { this->GridSize = GridSize; }
	CPoint getGridBoardSize() { return GridBoardSize; }
	void setGridBoardSize(CPoint GridBoardSize) { this->GridBoardSize = GridBoardSize; }
	CRect** getGridBoardRect() { return GridBoardRect; }
	void setGridBoardRect(CRect** GridBoardRect) { this->GridBoardRect = GridBoardRect; }
	CSpace** getGridBoard() { return GridBoard; }
	void setGridBoard(CSpace** GridBoard) { this->GridBoard = GridBoard; }

	void MakeGridBoard(CPoint WinSize);	//������ ����
};

