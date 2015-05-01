// Dib.h: interface for the CDib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIB_H_INCLUDED_)
#define AFX_DIB_H_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <vfw.h>
#pragma comment(lib,"vfw32.lib")

#define   _DIBTEST

#ifdef _DIBTEST
  #define   DIB_Save(x)    x
#else
  #define   DIB_Save(x)
#endif
class CDib : public CObject  
{
public:
	CDib();
	virtual ~CDib();

//Attributes
public:
	BYTE    *GetBits();
	CSize	 GetSize();
	LONG	 GetWidth();
	LONG	 GetHeight();
	int      GetBiBitCount();
	BOOL     IsValid()  { return(m_hDrawDib!=NULL); }
	operator HDRAWDIB() { return m_hDrawDib; }

//operations
public:
	BOOL Open(const char *pzFileName);
	BOOL Save(const char *pzFileName);
	void Draw(CDC *pDC,int nLeft, int nTop);
	void Close();

    static CString SelectBmpFile( CDib*  pDib );
    void SetBits( int width, int height, int pitch, const unsigned char* buf );

//public parameters
	BYTE		*m_pDibBits;
//implementation
public:
	BYTE		*m_pDib;
	HDRAWDIB	m_hDrawDib;

	BITMAPFILEHEADER bmpFileHeader;

	static void SaveImg8(const char* filename, const unsigned char * imgData,int iWidth,int iHeight, int xStep, BOOL bInvert = FALSE );

	static void TransTo256Gray( BYTE* pSrc, BYTE* pDst, int nWidth, int nHeight );


    void Clone( CDib* pDib);   //”…pDib Clone
};


//----------------------------------------------------------------------
BOOL Is256GrayPIC_608X304( CDib* );



BOOL bmpFileDirectory( CString strTitle, CString &  strdir );

//--------------------------------------------------------------------------------------------------------------
#endif // !defined(AFX_DIB_H_INCLUDED_)
