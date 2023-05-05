#pragma once
#include <list>
#include "TwelveModel.h"

#define NONE 15

class CTwelveViewModel
{
	CTwelveModel& Model = CTwelveModel::getInstance();
	CPoint ClickPoint;
public:
	void ReadyGame(CPoint winSize);
	void ResetGame();
	bool DoGame(CPoint clickPoint);

	std::list<CRect> DrawRectInfo();
	std::list<CGameTool::CImage> DrawImageInfo();
	std::list<CGameTool::CLog> DrawLogInfo();
};

