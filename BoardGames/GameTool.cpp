#include "pch.h"
#include "GameTool.h"

CRect CGameTool::PointToRect(CPoint point, CPoint size)
{
	CRect rect = CRect(point.x - (size.x / 2), point.y - (size.y / 2), point.x + (size.x / 2), point.y + (size.y / 2));

	return rect;
}

CImage CGameTool::SaveImage(PCWSTR filePath)
{
	CImage image;
	image.Load(filePath);

	return image;
}