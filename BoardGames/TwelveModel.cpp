#include "pch.h"
#include "TwelveModel.h"

//격자판에 관련된 모든 정보를 만든다
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridBoardRect = MakeGridBoardRect(WinSize, GridSize, GridBoardSize);
}