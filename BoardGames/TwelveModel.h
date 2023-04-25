#pragma once
#include "GridBoardTool.h"
class CTwelveModel : public CGridBoardTool
{
	CTwelveModel() {}
	CPoint GridSize = CPoint (100, 100);	//한 칸 크기
	CPoint GridBoardSize = CPoint(3, 4);	//격자판 크기
	CRect** GridBoardRect;					//격자판을 그릴 사각형
	CSpace** GridBoard;						//격자판의 사용 공간 정보
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

	void MakeGridBoard(CPoint WinSize);	//격자판 구현
};

