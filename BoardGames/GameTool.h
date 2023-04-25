#pragma once
class CGameTool
{
public:
	class CLog
	{
		CPoint point;
		CString text;
	public:
		CLog() {};

		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CString getText() { return text; }
		void setText(CString text) { this->text = text; }
	};

	class CSpace
	{
		CPoint point;
		CRect rect;
		CPoint itemIndex;
	public:
		CSpace() {}

		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CRect getRect() { return rect; }
		void setRect(CRect rect) { this->rect = rect; }
		CPoint getItemIndex() { return itemIndex; }
		void setItemIndex(CPoint itemIndex) { this->itemIndex = itemIndex; }
	};

	CRect PointToRect(CPoint point, CPoint size);
};

