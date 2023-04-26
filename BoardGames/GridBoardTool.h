#pragma once
#include "GameTool.h"

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint WinSize, CPoint GridSize, CPoint GridRectSize);						//격자판 생성
	CSpace** MakeGridSpace(CPoint WinSize, CPoint GridSize, CPoint GridSpaceSize, bool focusPoint);	//격자판 공간 생성
};