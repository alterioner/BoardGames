#pragma once
#include "GameTool.h"

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridBoardRect(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize);						//������ ����
	CSpace** MakeGridBoardSpace(CPoint WinSize, CPoint GridBoardSize, CPoint GridSize, bool focusPoint);	//������ ���� ����
};