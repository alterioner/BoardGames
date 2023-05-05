#pragma once

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
		CPoint point;	//아이템의 중심점
		CRect rect;		//아이템의 좌표

		CString side;	//아이템의 소속
		CString job;	//아이템의 직업
		CString status;	//아이템의 상태
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

	class CImage
	{
		CString filePath;
		CPoint point;
	public:
		CImage() {};
		CImage(CString filePath, CPoint point) : filePath(filePath), point(point) {}

		CString getFilePath() { return filePath; }
		void setFilePath(CString filePath) { this->filePath = filePath; }
		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
	};

	class CLog
	{
		CString text;	//텍스트
		CPoint point;	//로그가 위치할 좌표
		int align;		//TA 1:LEFT, 2:CENTER, 3:RIGHT
	public:
		CLog() {};
		CLog(CString text, CPoint point, int align) : text(text), point(point), align(align) {}

		CString getText() { return text; }
		void setText(CString text) { this->text = text; }
		CPoint getPoint() { return point; }
		void setPoint(CPoint point) { this->point = point; }
		int getAlign() { return align; }
		void setAlign(int align) { this->align = align; }
	};

	template <typename T>
	T GetInstance(T** data, CPoint index) { return data[index.x][index.y]; }

	CRect PointToRect(CPoint point, CPoint size);
};