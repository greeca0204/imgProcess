// ImgDoc.h : interface of the CImgDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGDOC_H__9729A1D3_8165_4C0A_92A0_4A4657EAD43F__INCLUDED_)
#define AFX_IMGDOC_H__9729A1D3_8165_4C0A_92A0_4A4657EAD43F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dib.h"
class CImgDoc : public CDocument
{
protected: // create from serialization only
	CImgDoc();
	DECLARE_DYNCREATE(CImgDoc)

// Attributes
public:
	CDib   m_dib;
	void Draw( CDC*);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImgDoc)
	afx_msg void OnReadbmp();
	afx_msg void OnFray();
	afx_msg void OnHist();
	afx_msg void OnD();
	afx_msg void OnP();
	afx_msg void OnOtsu();
	afx_msg void OnLap();
	afx_msg void OnExp();
	afx_msg void OnErode();
	afx_msg void OnDilate();
	afx_msg void OnFill();
	afx_msg void OnOpen();
	afx_msg void OnGrayerode();
	afx_msg void OnHit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGDOC_H__9729A1D3_8165_4C0A_92A0_4A4657EAD43F__INCLUDED_)
