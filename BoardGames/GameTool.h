#pragma once
#include <map>
#include <list>

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
		std::map<CString, CImage> Sprite;	//�������� �̹��� ��������Ʈ
		CImage image;

		CString side;	//�������� �Ҽ�
		CString job;	//�������� ����

		CPoint point;	//�������� �߽���
		CRect rect;		//�������� ��ǥ
		CString place;	//�������� ��ġ�� ���
	public:
		void insertSprite(CString key, CImage image) { Sprite[key] = image; }
		void removeSprite(CString key) { Sprite.erase(key); }
		CImage findSprite(CString key) { return Sprite[key]; }

		void setImage(CImage image) { this->image = image; }
		CImage getImage() { return image; }

		CString getSide() { return side; }
		void setSide(CString side) { this->side = side; }
		CString getJob() { return job; }
		void setJob(CString job) { this->job = job; }

		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		CRect getRect() { return rect; }
		void setRect(CRect rect) { this->rect = rect; }
		CString getPlace() { return place; }
		void setPlace(CString place) { this->place = place; }
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

	CRect PointToRect(CPoint point, CPoint size);
	CImage SaveImage(PCWSTR filePath);
};