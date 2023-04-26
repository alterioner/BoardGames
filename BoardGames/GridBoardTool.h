#pragma once
#include "GameTool.h"

#define NONE 15

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint winSize, CPoint gridSize, CPoint gridRectSize);						//격자판 생성
	CSpace** MakeGridSpace(CPoint winSize, CPoint gridSize, CPoint gridSpaceSize, bool focusPoint);	//격자판 공간 생성
	CPoint PointToGridSpaceIndex(CSpace** gridSpace, CPoint gridSpaceSize, CPoint clickPoint);		//격자판 활성화
	void MoveSpaceInfo(CSpace** gridSpace, CPoint originalIndex, CPoint nextIndex);					//격자판 아이템 인덱스 정보 갱신
};