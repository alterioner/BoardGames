#pragma once
#include <map>
#include <list>

class CGameTool
{
public:
	class CSpace
	{
		CPoint point;		//한 칸의 중심점
		CRect rect;			//한 칸을 그릴 사각형
		CPoint itemIndex;	//자신의 칸에 위치한 아이템 인덱스
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
		std::map<CString, CImage> Sprite;	//아이템의 이미지 스프라이트
		CImage image;

		CString side;	//아이템의 소속
		CString job;	//아이템의 직업

		CPoint point;	//아이템의 중심점
		CRect rect;		//아이템의 좌표
		CString place;	//아이템의 위치한 장소
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
		CPoint point;	//로그가 위치할 좌표
		CString text;	//텍스트
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