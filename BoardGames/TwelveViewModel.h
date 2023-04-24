#pragma once
#include <tuple>
#include "TwelveModel.h"

class CTwelveViewModel
{
	CTwelveModel model;
public:
	void SetGame(CPoint WinSize);
	std::tuple<CRect*, int> Game(CPoint WinSize);
};

