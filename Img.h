// Img.h : main header file for the IMG application
//

#if !defined(AFX_IMG_H__FA0A15FE_F678_4123_8B88_E5196D7CC7AE__INCLUDED_)
#define AFX_IMG_H__FA0A15FE_F678_4123_8B88_E5196D7CC7AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImgApp:
// See Img.cpp for the implementation of this class
//

class CImgApp : public CWinApp
{
public:
	CImgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImgApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMG_H__FA0A15FE_F678_4123_8B88_E5196D7CC7AE__INCLUDED_)
