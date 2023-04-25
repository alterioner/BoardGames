
// BoardGamesView.h: CBoardGamesView 클래스의 인터페이스
//

#pragma once
#include <tuple>
#include "TwelveViewModel.h"

class CBoardGamesView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBoardGamesView() noexcept;
	DECLARE_DYNCREATE(CBoardGamesView)

// 특성입니다.
public:
	CBoardGamesDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CBoardGamesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	CPoint WinSize;	//윈도우 사이즈
	CTwelveViewModel Twelve;
	std::tuple<CRect*, int, CGameTool::CLog*, int> GameTuple;
};

#ifndef _DEBUG  // BoardGamesView.cpp의 디버그 버전
inline CBoardGamesDoc* CBoardGamesView::GetDocument() const
   { return reinterpret_cast<CBoardGamesDoc*>(m_pDocument); }
#endif

