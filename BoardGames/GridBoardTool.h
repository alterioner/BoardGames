#pragma once
#include "GameTool.h"

#define NONE 15

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint winSize, CPoint gridSize, CPoint gridRectSize);						//������ ����
	CSpace** MakeGridSpace(CPoint winSize, CPoint gridSize, CPoint gridSpaceSize, bool focusPoint);	//������ ���� ����
	CPoint PointToGridSpaceIndex(CSpace** gridSpace, CPoint gridSpaceSize, CPoint clickPoint);		//������ Ȱ��ȭ
	void MoveSpaceInfo(CSpace** gridSpace, CPoint originalIndex, CPoint nextIndex);					//������ ������ �ε��� ���� ����
};