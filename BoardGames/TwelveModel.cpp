#include "pch.h"
#include "TwelveModel.h"

//�����ǿ� ���õ� ��� ���� ����
void CTwelveModel::MakeGridBoard(CPoint WinSize)
{
	GridBoardRect = MakeGridBoardRect(WinSize, GridBoardSize, GridSize);		//������ ����
	GridBoard = MakeGridBoardSpace(WinSize, GridBoardSize, GridSize, false);	//�������� ��� ���� ����
}