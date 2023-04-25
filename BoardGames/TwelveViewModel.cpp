#include "pch.h"
#include "TwelveViewModel.h"

void CTwelveViewModel::SetGame(CPoint WinSize)
{
	model.MakeGridBoard(WinSize);
}

std::tuple<CRect*, int, CGameTool::CLog*, int> CTwelveViewModel::Game(CPoint WinSize)
{

	CRect** rectBoard = model.getGridBoardRect();

	int col = model.getGridSize().x;
	int row = model.getGridSize().y;

	CRect* rect = new CRect[col + row];
	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			rect[(c * 4) + r] = rectBoard[c][r];
		}
	}

	CGameTool::CLog* log;
	int col = 3;
	int row = 4;

	int totalWidth = col * 100;	//���� ����
	int totalHeight = row * 100;	//���� ����

	int startX = (WinSize.x / 2) - (totalWidth / 2);		//���尡 ������ x��ǥ
	int startY = (WinSize.y / 2) - (totalHeight / 2);	//���尡 ������ y��ǥ

	CGameTool::CSpace** spaceBoard;
	CGameTool::CLog* log;

	CString gridIndex;

	bool focusPoint = false;
	if (focusPoint)
	{
		col++; row++;
		log = new CGameTool::CLog[col * row];

		spaceBoard = new CGameTool::CSpace * [col];
		for (int c = 0; c < col; c++)
		{
			spaceBoard[c] = new CGameTool::CSpace[row];
			for (int r = 0; r < row; r++)
			{
				spaceBoard[c][r].setPoint(CPoint(startX + (100 * c), startY + (100 * r)));		//�� ���� �߽��� ��ǥ ����
				spaceBoard[c][r].setRect(PointToRect(spaceBoard[c][r].getPoint(), 100, 100));	//�� ���� ���� ��ǥ ����
				log[c * row + r].setPoint(spaceBoard[c][r].getPoint());
				gridIndex.Format(_T("%d, %d"), log[c * row + r].getPoint().x, log[c * row + r].getPoint().y);
				log[(c * row) + r].setText(gridIndex);
			}
		}
	}
	else
	{
		log = new CGameTool::CLog[col * row];
		spaceBoard = new CGameTool::CSpace * [col];
		for (int c = 0; c < col; c++)
		{
			spaceBoard[c] = new CGameTool::CSpace[row];
			for (int r = 0; r < row; r++)
			{
				spaceBoard[c][r].setPoint(CPoint(startX + (100 * c) + (100 / 2), startY + (100 * r) + (100 / 2)));	//�� ĭ�� �߽��� ��ǥ ����
				spaceBoard[c][r].setRect(PointToRect(spaceBoard[c][r].getPoint(), 100, 100));							//�� ĭ�� ���� ��ǥ ����
				log[c * row + r].setPoint(spaceBoard[c][r].getPoint());
				gridIndex.Format(_T("%d, %d"), log[c * row + r].getPoint().x, log[c * row + r].getPoint().y);
				log[(c * row) + r].setText(gridIndex);

			}
		}
	}

	return std::make_tuple(rect, 12, log, 12);
}