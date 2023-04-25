#pragma once
#include "GameTool.h"

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridBoardRect(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize);						//격자판 생성
	CSpace** MakeGridBoardSpace(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize, bool focusPoint);	//격자판 공간 생성
};