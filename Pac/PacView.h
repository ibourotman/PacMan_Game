
// PacView.h : interface of the CPacView class
//

#pragma once
class CPacMap;
#include <thread>

class CPacView : public CView
{
protected: // create from serialization only
	CPacView();
	DECLARE_DYNCREATE(CPacView)
private:
	CPacMap* m_pMap;
	std::thread* m_pThread;
// Attributes
public:
	CPacDoc* GetDocument() const;
	bool m_bFlag;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPacView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnGameOver(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PacView.cpp
inline CPacDoc* CPacView::GetDocument() const
   { return reinterpret_cast<CPacDoc*>(m_pDocument); }
#endif

