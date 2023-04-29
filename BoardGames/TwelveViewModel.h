#pragma once
#include <tuple>
#include "TwelveModel.h"

#define NONE 15

class CTwelveViewModel
{
	CTwelveModel& Model = CTwelveModel::getInstance();
	CPoint ClickPoint;

	CPoint MoveItemIndex = CPoint(NONE, NONE);
public:
	void ReadyGame(CPoint winSize);
	void ResetGame();
	bool DoGame(CPoint clickPoint);

	std::tuple<CRect*, int> DrawRectInfo();
	std::tuple<CString*, CPoint*, int> DrawImageInfo();
	std::tuple<CGameTool::CLog*, int> DrawLogInfo();
};

