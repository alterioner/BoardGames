
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
		start = false;
	}
	if (reset)
	{
		Twelve.ResetGame();
		reset = false;
	}
	animating = Twelve.DoGame(clickPoint);

	DrawRectTuple = Twelve.DrawRectInfo();
	CRect* rect = std::get<0>(DrawRectTuple);
	int rectSize = std::get<1>(DrawRectTuple);

	for (int i = 0; i < rectSize; i++)
	{
		pDC->Rectangle(rect[i]);
	}

	DrawImageTuple = Twelve.DrawImageInfo();
	filePath = std::get<0>(DrawImageTuple);
	imagePoint = std::get<1>(DrawImageTuple);
	imageSize = std::get<2>(DrawImageTuple);

	//Draw(pDC, Model.getItem()[3][0].findSprite(L"GKing"), CPoint(300, 300));
	
	image.Load(L"res/Twelve/GKing.png");
	//Model.getItem()[3][0].setImage(image);

	int width = image.GetWidth();		//이미지의 넓이 저장
	int height = image.GetHeight();		//이미지의 높이 저장

	image.Draw(pDC->m_hDC, 300 - (width / 2), 300 - (height / 2));	//이미지가 입력된 위치의 가운데에 그려지게 조정
	image.Detach();
	//Draw(pDC, image2, CPoint(300, 300));
	

	for (int i = 0; i < imageSize; i++)
	{
		DrawFromFile(pDC, filePath[i], imagePoint[i]);
	}

	DrawLogTuple = Twelve.DrawLogInfo();
	CGameTool::CLog* log = std::get<0>(DrawLogTuple);
	int logSize = std::get<1>(DrawLogTuple);

	for (int i = 0; i < logSize; i++)
	{
		switch(log[i].getAlign())
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

		pDC->TextOut(log[i].getPoint().x, log[i].getPoint().y, log[i].getText());
	}
	  
	pDC->TextOut(10, 150, str);

	if (animating) {
		CPoint index = Model.getActiveItemIndex();
		Draw(pDC, filePath[index.x * 2 + index.y]);
		Invalidate();
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

	Invalidate();
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

void CBoardGamesView::Draw(CDC* pDC, CImage image, CPoint point)
{
	int width = image.GetWidth();		//이미지의 넓이 저장
	int height = image.GetHeight();		//이미지의 높이 저장

	image.Draw(pDC->m_hDC, point.x - (width / 2), point.y - (height / 2));	//이미지가 입력된 위치의 가운데에 그려지게 조정
	image.Detach();
}

void CBoardGamesView::Draw(CDC* pDC, CString filename)
{

	CPoint movingPoint;							//말이 그려질 위치
	CPoint depart = Model.getOriginalPoint();
	CPoint arrive = Model.getNextPoint();
	CPoint move = arrive - depart;

	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라

	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라
	//이미지 캐싱 해놔라

	if (imgFrame == 0)										//0프레임
	{
		movingPoint.x = depart.x + (move.x * 0.5);		//출발위치와 도착위치의 중간에 위치
		movingPoint.y = depart.y + (move.y * 0.5);
		imgFrame++;
	}
	else if (imgFrame == 1)									//1프레임
	{
		movingPoint.x = depart.x + (move.x * 0.8);		//출발위치와 도착위치의 4/5에 위치
		movingPoint.y = depart.y + (move.y * 0.8);
		imgFrame++;
	}
	else if (imgFrame < 8)
	{
		movingPoint = arrive;							//도착위치에 위치
		imgFrame++;
	}
	else
	{
		movingPoint = arrive;							//도착위치에 위치
		imgFrame = 0;
	}

	DrawFromFile(pDC, filename, movingPoint);
	str.Format(_T("%d, %d"), imgFrame, movingPoint.y);
}