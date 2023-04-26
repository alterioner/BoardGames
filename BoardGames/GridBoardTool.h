#pragma once
#include "GameTool.h"

#define NONE 15

class CGridBoardTool : public CGameTool
{
public:
	CRect** MakeGridRect(CPoint winSize, CPoint gridSize, CPoint gridRectSize);						//����ĭ ����
	CSpace** MakeGridSpace(CPoint winSize, CPoint gridSize, CPoint gridSpaceSize, bool focusPoint);	//���ڰ��� ����
	CPoint PointToGridSpaceIndex(CSpace** gridSpace, CPoint gridSpaceSize, CPoint point);			//��ǥ�� ���ڰ��� �ε����� ��ȯ
};