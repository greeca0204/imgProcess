// ImgView.cpp : implementation of the CImgView class
//

#include "stdafx.h"
#include "Img.h"

#include "ImgDoc.h"
#include "ImgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgView

IMPLEMENT_DYNCREATE(CImgView, CView)

BEGIN_MESSAGE_MAP(CImgView, CView)
	//{{AFX_MSG_MAP(CImgView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgView construction/destruction

CImgView::CImgView()
{
	// TODO: add construction code here

}

CImgView::~CImgView()
{
}

BOOL CImgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImgView drawing

void CImgView::OnDraw(CDC* pDC)
{
	CImgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDoc->Draw(pDC );
}

/////////////////////////////////////////////////////////////////////////////
// CImgView printing

BOOL CImgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImgView diagnostics

#ifdef _DEBUG
void CImgView::AssertValid() const
{
	CView::AssertValid();
}

void CImgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgDoc* CImgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgDoc)));
	return (CImgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgView message handlers
