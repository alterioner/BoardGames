#pragma once

class CGameTool
{
public:
	class CSpace
	{
		CPoint point;		//�� ĭ�� �߽���
		CRect rect;			//�� ĭ�� �׸� �簢��
		CPoint itemIndex;	//�ڽ��� ĭ�� ��ġ�� ������ �ε���
	public:
		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CRect getRect() { return rect; }
		void setRect(CRect rect) { this->rect = rect; }
		CPoint getItemIndex() { return itemIndex; }
		void setItemIndex(CPoint itemIndex) { this->itemIndex = itemIndex; }
	};


	class CItem
	{
		CPoint point;	//�������� �߽���
		CRect rect;		//�������� ��ǥ

		CString side;	//�������� �Ҽ�
		CString job;	//�������� ����
		CString status;	//�������� ����
	public:
		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CRect getRect() { return rect; }
		void setRect(CRect rect) { this->rect = rect; }

		CString getSide() { return side; }
		void setSide(CString side) { this->side = side; }
		CString getJob() { return job; }
		void setJob(CString job) { this->job = job; }
		CString getStatus() { return status; }
		void setStatus(CString status) { this->status = status; }
	};

	class CLog
	{
		CPoint point;	//�αװ� ��ġ�� ��ǥ
		CString text;	//�ؽ�Ʈ
		int align;		//TA 1:LEFT, 2:CENTER, 3:RIGHT
	public:
		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CString getText() { return text; }
		void setText(CString text) { this->text = text; }
		int getAlign() { return align; }
		void setAlign(int align) { this->align = align; }
	};

	template <typename T>
	T GetInstance(T** Data, CPoint index) { return Data[index.x][index.y]; }

	CRect PointToRect(CPoint point, CPoint size);
};