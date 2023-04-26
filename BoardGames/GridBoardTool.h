#pragma once
#include "GameTool.h"

#define NONE 15

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint winSize, CPoint gridSize, CPoint gridRectSize);						//격자칸 생성
	CSpace** MakeGridSpace(CPoint winSize, CPoint gridSize, CPoint gridSpaceSize, bool focusPoint);	//격자공간 생성
	CPoint PointToGridSpaceIndex(CSpace** gridSpace, CPoint gridSpaceSize, CPoint point);			//좌표를 격자공간 인덱스로 변환
};