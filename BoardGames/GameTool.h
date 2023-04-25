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
		CPoint point;		//한 칸의 중심점
		CRect rect;			//한 칸을 그릴 좌표
		CPoint ItemIndex;	//자신의 칸에 위치한 아이템 인덱스
	public:
		CSpace() {}
		virtual ~CSpace() {}

		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CRect getRect() { return rect; }
		void setRect(CRect rect) { this->rect = rect; }
		CPoint getItemIndex() { return ItemIndex; }
		void setItemIndex(CPoint index) { this->ItemIndex = index; }
	};
};

