#include "pch.h"
#include "TwelveModel.h"

//격자판에 관련된 모든 정보 구현
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridBoardRect = MakeGridBoardRect(WinSize, GridBoardSize, GridSize);		//격자판 생성
	GridBoard = MakeGridBoardSpace(WinSize, GridBoardSize, GridSize, false);	//격자판의 사용 공간 생성
}