#pragma once
#include "GridBoardTool.h"
class CTwelveModel : public CGridBoardTool
{
	CPoint GridSize = CPoint(100, 100);		//한 칸 크기
	CPoint GridBoardSize = CPoint(3, 4);	//격자판 크기
	CRect** GridBoardRect;					//격자판 그릴 때 쓰이는 사각형
	CGameTool::CSpace** GridBoard;			//격자판 정보
public:
	CPoint getGridSize() { return GridSize; }
	void setGridSize(CPoint GridSize) { this->GridSize = GridSize; }
	CPoint getGridBoardSize() { return GridBoardSize; }
	void setGridBoardSize(CPoint GridBoardSize) { this->GridBoardSize = GridBoardSize; }
	CRect** getGridBoardRect() { return GridBoardRect; }
	void setGridBoardRect(CRect** GridBoardRect) { this->GridBoardRect = GridBoardRect; }

	void MakeGridBoard(CPoint WinSize);	//격자판 만들기
};

