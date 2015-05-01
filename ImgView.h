// ImgView.h : interface of the CImgView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGVIEW_H__AB7A6E2B_CD6E_45F1_92FF_60886AD2684E__INCLUDED_)
#define AFX_IMGVIEW_H__AB7A6E2B_CD6E_45F1_92FF_60886AD2684E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImgView : public CView
{
protected: // create from serialization only
	CImgView();
	DECLARE_DYNCREATE(CImgView)

// Attributes
public:
	CImgDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImgView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImgView.cpp
inline CImgDoc* CImgView::GetDocument()
   { return (CImgDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGVIEW_H__AB7A6E2B_CD6E_45F1_92FF_60886AD2684E__INCLUDED_)
