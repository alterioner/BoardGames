#include "pch.h"
#include "GridBoardTool.h"

//������ ũ���, �� ĭ�� ũ���, ĭ ������ �޾� �������� �����
CRect** CGridBoardTool::MakeGridBoardRect(CPoint WinSize, CPoint GridSize, CPoint GridBoardSize)
{
	int col = GridBoardSize.x;
	int row = GridBoardSize.y;

	int width = GridSize.x;
	int heigtht = GridSize.y;

	int totalwidth = col * width;		//�׷��� ���� ����
	int totalheight = row * heigtht;	//�׷��� ���� ����

	int startX = (WinSize.x / 2) - (totalwidth / 2);	//���尡 �׷����� ������ ��ġ(���� �ȼ�)
	int startY = (WinSize.y / 2) - (totalheight / 2);	//���尡 �׷����� ������ ��ġ(���� �ȼ�)

	CRect** rectBoard = new CRect * [col];

	for (int c = 0; c < col; c++)
	{
		rectBoard[c] = new CRect[row];
		for (int r = 0; r < row; r++)
		{
			rectBoard[c][r] = CRect(startX + (width * c), startY + (heigtht * r), startX + (width * (c + 1)), startY + (heigtht * (r + 1)));
		}
	}

	return rectBoard;
}