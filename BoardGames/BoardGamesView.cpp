
// BoardGamesView.cpp: CBoardGamesView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BoardGames.h"
#endif

#include "BoardGamesDoc.h"
#include "BoardGamesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBoardGamesView

IMPLEMENT_DYNCREATE(CBoardGamesView, CView)

BEGIN_MESSAGE_MAP(CBoardGamesView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CBoardGamesView 생성/소멸

CBoardGamesView::CBoardGamesView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CBoardGamesView::~CBoardGamesView()
{
}

BOOL CBoardGamesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBoardGamesView 그리기

void CBoardGamesView::OnDraw(CDC* pDC)
{
	CBoardGamesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (start)
	{
		Twelve.ReadyGame(WinSize);
		Twelve.ResetGame();
		start = false;
	}

	if (reset)
	{
		Twelve.ResetGame();
		reset = false;
	}

	animating = Twelve.DoGame(clickPoint);

	pDC->Rectangle(CRect(CPoint(-1, -1), CPoint(WinSize.x + 1, WinSize.y + 1)));

	DrawRectList = Twelve.DrawRectInfo();
	for (auto& rect : DrawRectList) pDC->Rectangle(rect);

	DrawImageList = Twelve.DrawImageInfo();
	for (auto& image : DrawImageList) DrawFromFile(pDC, image.getFilePath(), image.getPoint());

	DrawLogList = Twelve.DrawLogInfo();
	for (auto& log : DrawLogList)
	{
		switch (log.getAlign())
		{
		case 1:
			pDC->SetTextAlign(TA_LEFT);
			break;
		case 2:
			pDC->SetTextAlign(TA_CENTER);
			break;
		case 3:
			pDC->SetTextAlign(TA_RIGHT);
			break;
		}

		pDC->TextOut(log.getPoint().x, log.getPoint().y, log.getText());
	}

	Winner = Twelve.CheckWinner();
	if (Winner != L"None")
	{
		reset = true;
		MessageBox(Winner, NULL, MB_OK);
		Invalidate(0);
	}

	if (animating)
	{
		Sleep(100);
		Invalidate(0);
	}
}

void CBoardGamesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBoardGamesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBoardGamesView 진단

#ifdef _DEBUG
void CBoardGamesView::AssertValid() const
{
	CView::AssertValid();
}

void CBoardGamesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBoardGamesDoc* CBoardGamesView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBoardGamesDoc)));
	return (CBoardGamesDoc*)m_pDocument;
}
#endif //_DEBUG


// CBoardGamesView 메시지 처리기


void CBoardGamesView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	WinSize.x = cx;
	WinSize.y = cy;
}

void CBoardGamesView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	clickPoint = point;

	Invalidate(0);
	CView::OnLButtonUp(nFlags, point);
}

//중심점과 이미지 파일 경로를 받아 이미지를 그려줌 (CGameTool)
//(CDC*, CPoint, PCWSTR filePath)
bool CBoardGamesView::DrawFromFile(CDC* pDC, PCWSTR filePath, CPoint point)
{
	CImage image;

	if (FAILED(image.Load(filePath)))
	{
		return FALSE;
	}

	int width = image.GetWidth();		//이미지의 넓이 저장
	int height = image.GetHeight();		//이미지의 높이 저장

	image.Draw(pDC->m_hDC, point.x - (width / 2), point.y - (height / 2));	//이미지가 입력된 위치의 가운데에 그려지게 조정
	image.Detach();

	return TRUE;
}