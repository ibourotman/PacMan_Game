
// PacView.cpp : implementation of the CPacView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Pac.h"
#endif

#include "PacDoc.h"
#include "PacView.h"
#include "PacMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

UINT DrawThread(void* p);
// CPacView

IMPLEMENT_DYNCREATE(CPacView, CView)

BEGIN_MESSAGE_MAP(CPacView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPacView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(UM_GAMEOVER, &CPacView::OnGameOver)
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPacView construction/destruction

CPacView::CPacView() : m_pMap(nullptr), m_bFlag(true), m_pThread(nullptr)
{

}

CPacView::~CPacView()
{
}

BOOL CPacView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CPacView drawing

void CPacView::OnDraw(CDC* pDC)
{
	CPacDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC MemDC;
	CRect rect;
	GetClientRect(&rect);
	MemDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = (CBitmap*)MemDC.SelectObject(&bitmap);

	if (m_pMap)
		m_pMap->Draw(&MemDC);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	// TODO: add draw code for native data here
}


// CPacView printing


void CPacView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPacView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPacView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPacView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPacView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPacView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPacView diagnostics

#ifdef _DEBUG
void CPacView::AssertValid() const
{
	CView::AssertValid();
}

void CPacView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPacDoc* CPacView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPacDoc)));
	return (CPacDoc*)m_pDocument;
}
#endif //_DEBUG


// CPacView message handlers

void CPacView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_pThread = new thread(DrawThread, this);
	m_pMap = new CPacMap(m_hWnd);

}


void CPacView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_pMap)
	{
		m_pMap->OnKeyDown(nChar);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CPacView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

UINT DrawThread(void* p)
{
	CPacView* pView = (CPacView*)p;
	while (pView->m_bFlag)
	{
		pView->Invalidate(0);
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	return 0;
}

void CPacView::OnDestroy()
{
	CView::OnDestroy();

	m_bFlag = false;
	if (m_pThread)
	{
		m_pThread->join();
		delete m_pThread;
		m_pThread = nullptr;
	}
	delete m_pMap;
}

LRESULT CPacView::OnGameOver(WPARAM wParam, LPARAM lParam)
{
	delete m_pMap;
	m_pMap = new CPacMap(m_hWnd);
	return LRESULT();
}
