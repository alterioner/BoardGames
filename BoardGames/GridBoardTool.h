#pragma once
#include "GameTool.h"

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint WinSize, CPoint GridSize, CPoint GridRectSize);						//������ ����
	CSpace** MakeGridSpace(CPoint WinSize, CPoint GridSize, CPoint GridSpaceSize, bool focusPoint);	//������ ���� ����
};