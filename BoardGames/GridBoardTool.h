#pragma once
#include "GameTool.h"

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridBoardRect(CPoint WinSize, CPoint GridSize, CPoint GridBoardSize);	//������ �����
};