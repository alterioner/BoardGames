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
		CPoint point;		//�� ĭ�� �߽���
		CRect rect;			//�� ĭ�� �׸� ��ǥ
		CPoint ItemIndex;	//�ڽ��� ĭ�� ��ġ�� ������ �ε���
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

