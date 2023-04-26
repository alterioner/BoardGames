#pragma once
#include <tuple>
#include "TwelveModel.h"

#define NONE 15

class CTwelveViewModel
{
	CTwelveModel& model = CTwelveModel::getInstance();
	CPoint clickPoint;
public:
	void ReadyGame(CPoint WinSize);
	void ResetGame();
	void DoGame(CPoint clickPoint);

	std::tuple<CRect*, int> DrawRectInfo();
	std::tuple<CString*, CPoint*, int> DrawImageInfo();
	std::tuple<CGameTool::CLog*, int> DrawLogInfo();
};

