// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Dib.h"
#include < shlobj.h >

//#include "kxMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	m_hDrawDib=NULL;
	m_pDib=NULL;
}

CDib::~CDib()
{
	Close();
}

void CDib::Draw(CDC *pDC,int nLeft, int nTop)
{
	/*if(m_pDib!=NULL)
	{
	ASSERT(IsValid());
	DrawDibRealize(m_hDrawDib,pDC->GetSafeHdc(),TRUE);
	DrawDibDraw(m_hDrawDib,pDC->GetSafeHdc(),
				0,  //desktop left
				0,  //desktop top
				nWidth,
				nHeight,
				(BITMAPINFOHEADER *)m_pDib,
				(LPVOID) GetBits(),
				0,  //source left
				0,  //source top
				((BITMAPINFOHEADER *)m_pDib)->biWidth,
				((BITMAPINFOHEADER *)m_pDib)->biHeight,
				DDF_BACKGROUNDPAL);
	}*/
	if(m_pDib!=NULL)
	{
	ASSERT(IsValid());
	DrawDibRealize(m_hDrawDib,pDC->GetSafeHdc(),TRUE);
	DrawDibDraw(m_hDrawDib,pDC->GetSafeHdc(),
				nLeft,  //desktop left
				nTop,  //desktop top
				((BITMAPINFOHEADER *)m_pDib)->biWidth,
				((BITMAPINFOHEADER *)m_pDib)->biHeight,
				(BITMAPINFOHEADER *)m_pDib,
				(LPVOID) GetBits(),
				0,  //source left
				0,  //source top
				((BITMAPINFOHEADER *)m_pDib)->biWidth,
				((BITMAPINFOHEADER *)m_pDib)->biHeight,
				DDF_BACKGROUNDPAL);
	}
}

CSize CDib::GetSize()
{
	return CSize(((BITMAPINFOHEADER *)m_pDib)->biWidth,
				 ((BITMAPINFOHEADER *)m_pDib)->biHeight);	
}

LONG CDib::GetWidth()
{
	return ((BITMAPINFOHEADER *)m_pDib)->biWidth;
}

LONG CDib::GetHeight()
{
	return	((BITMAPINFOHEADER *)m_pDib)->biHeight;
}

void CDib::Close()
{
	if(m_hDrawDib!=NULL)
	{
		DrawDibClose(m_hDrawDib);
		m_hDrawDib=NULL;
	}

	if(m_pDib!=NULL)
	{
		delete []m_pDib;
		m_pDib=NULL;
	}
}

BOOL CDib::Open(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

	Close();

	//drawdibopen initialize the diradib library and 
	//returns a handle for all drawdib operations
	if(!(m_hDrawDib=DrawDibOpen()))
		goto exit;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeRead | CFile::typeBinary))
		goto exit;

	if(file.Read((void *)&bmpFileHeader,nBmpFileHeaderSize)!=(UINT)nBmpFileHeaderSize)
		goto failure;

	//validate the DIB file header by checking the first
	//two characters for the signature "BM"
	if(bmpFileHeader.bfType!=*((WORD *)"BM"))
		goto failure;

	//allocate a big chuck of global memory to store the DIB
	m_pDib=(BYTE *)new unsigned char [bmpFileHeader.bfSize-nBmpFileHeaderSize];

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.Read(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	if(((BITMAPINFOHEADER *)m_pDib)->biSizeImage==0)
	{
		//the application that create this bitmap didn't fill
		//in the biSizeImage field. Let's fill it
		//in even though the DrawDib * functions don't need it.
		BITMAPINFOHEADER *pDib=(BITMAPINFOHEADER *)m_pDib;

		//scan lines must be DWord aligned, hence the strange bit stuff
		pDib->biSizeImage=((((pDib->biWidth*pDib->biBitCount)+31)&~31)>>3)*pDib->biHeight;
	}

	m_pDibBits=GetBits();

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	Close();
	return FALSE;
}

BOOL CDib::Save(const char * pzFileName)
{
//	BITMAPFILEHEADER bmpFileHeader;
	CFile file;
	int nBmpFileHeaderSize;

 	//open and read the DIB file header
	nBmpFileHeaderSize=sizeof(BITMAPFILEHEADER);

	if(!file.Open(pzFileName,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
		goto exit;

	file.Write(&bmpFileHeader,nBmpFileHeaderSize); 

	//allocate memory fail
	if(!m_pDib)
		goto failure;

	//read the dib into the buffer at a time using ReadHuge
	file.Write(m_pDib,bmpFileHeader.bfSize-nBmpFileHeaderSize);

	file.Close();
	return TRUE;

failure:
	file.Close();
exit:
	return FALSE;
}

BYTE * CDib::GetBits()
{
	//the size of the color map is determined by the number
	//of RGBQUAD structures presend.
	//it also depends on the bit_depth of the Dib
	DWORD dwNumColors,dwColorTableSize;
	BITMAPINFOHEADER *lpDib=(BITMAPINFOHEADER *)m_pDib;

	WORD wBitCount=lpDib->biBitCount;

	if(lpDib->biSize>=36)
		dwNumColors=lpDib->biClrUsed;
	else
		dwNumColors=0;

	if(dwNumColors==0)
	{
		if(wBitCount!=24)
			dwNumColors=1L<<wBitCount;
		else 
			dwNumColors=0;
	}

	dwColorTableSize=dwNumColors*sizeof(RGBQUAD);

	return m_pDib+lpDib->biSize+dwColorTableSize;
}

int CDib::GetBiBitCount()
{
	if(m_pDib!=NULL)
		return ((BITMAPINFOHEADER *)m_pDib)->biBitCount; 
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
BOOL Is256GrayPIC_608X304( CDib* pDib )
{//检查位图是否是256灰度，大小608 * 304
	if ( pDib == NULL || !pDib->IsValid() )
		return FALSE;
    return pDib->GetBiBitCount() == 8 && pDib->GetHeight() == 304 && pDib->GetWidth() == 608;
}

CString CDib::SelectBmpFile( CDib*  pDib )
{
    CFileDialog dlg   (TRUE,    // Open
                       NULL,    // No default extension
                       NULL,    // No initial file name
                       OFN_FILEMUSTEXIST| OFN_HIDEREADONLY,

                       _T( "All Picture Files (*.bmp;*.dib;*.emf;*.gif;*.ico;*.jpg;*.wmf)|"
					   "*.bmp;*.dib;*.emf;*.gif;*.ico;*.jpg;*.wmf|"
                       "Bitmap Files (*.DIB;*.BMP)|*.DIB;*.BMP|"  
					   "Jpeg Files (*.Jpg;*.Jpeg)|*.Jpg;*.Jpeg|"
                       "GIF Files (*.gif)|*.gif|"
					   "Windows Icons (*.ico)|*.ico|"
					   "EMF Files(*.emf)|*.emf|"
					   "WMF Files(*.wmf)|*.wmf|"
					   "All Files (*.*)|*.*||" ) );

	CString     strFullfile;
	
	if (dlg.DoModal() == IDOK) 
	{
		strFullfile = dlg.GetPathName();
		if ( pDib )
		{
			if ( pDib->Open( strFullfile ) == FALSE )
				strFullfile.Empty();
			else
			{

			}
		}
	}
	return strFullfile;
}


void CDib::SaveImg8(const char* filename, const unsigned char * imgData,int iWidth,int iHeight, int xStep, BOOL bInvert )
{
	unsigned char temp[44];
	memset(temp,0,44);
	//定义图形大小
	int iWidthDW8  = (iWidth*8+31)/32*4;
	//图形格式参数
	//LPBITMAPINFO lpbmih = new BITMAPINFO;
	BITMAPINFO* lpbmih;
	lpbmih = (BITMAPINFO*)temp;//malloc(sizeof(BITMAPINFO));
	lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbmih->bmiHeader.biWidth = iWidth;
	lpbmih->bmiHeader.biHeight = iHeight;
	lpbmih->bmiHeader.biPlanes = 1;
	lpbmih->bmiHeader.biBitCount = 8;
	lpbmih->bmiHeader.biCompression = 0;//BI_RGB;
	lpbmih->bmiHeader.biSizeImage = 0;
	lpbmih->bmiHeader.biXPelsPerMeter = 0;
	lpbmih->bmiHeader.biYPelsPerMeter = 0;
	lpbmih->bmiHeader.biClrUsed = 0;
	lpbmih->bmiHeader.biClrImportant = 0;
	
	//创建位图数据
	//保存到文件并创建位图结构
	BITMAPFILEHEADER bmfh;
	//ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));
	memset(&bmfh,0,sizeof(BITMAPFILEHEADER));
	*((char *)&bmfh.bfType) = 'B';
	*(((char *)&bmfh.bfType) + 1) = 'M';
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD);
	bmfh.bfSize = bmfh.bfOffBits + iWidthDW8 * iHeight;
	
	//调色板
	RGBQUAD rgbQuad[256];
	
	for( int i=0;i<256;i++)
	{
		rgbQuad[i].rgbBlue=i;
		rgbQuad[i].rgbGreen=i;
		rgbQuad[i].rgbRed=i;
		rgbQuad[i].rgbReserved=0;
	}
	
	FILE*   fp = fopen( filename, "wb" );
	//if( fopen_s( &fp, filename, "wb" ) == 0 )
	if( fp )
	{
		fwrite(&bmfh,sizeof(BITMAPFILEHEADER), 1, fp);
		fwrite(&(lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER), 1, fp);
		fwrite(rgbQuad,256*sizeof(RGBQUAD), 1, fp);
		if( bInvert )
		{
		    for( int y = 0 ; y < iHeight ; ++y)
		    {//上下颠倒一行一行写
			    fwrite(imgData + (iHeight-1-y)*xStep, iWidthDW8, 1, fp );
			    //imgData += xStep;//iWidthDW8;//iWidth;
		    }
		}
		else
		{
		    for( int y = 0 ; y < iHeight ; ++y)
		    { 
			    fwrite(imgData,iWidthDW8, 1, fp );
			    imgData += xStep;//iWidthDW8;//iWidth;
		    }
		}
		fclose(fp);
	}
	else
	{
		TRACE( "Save Bmp Err\n" );
	}
	
}

void CDib::TransTo256Gray( BYTE* pSrc, BYTE* pDst, int nWidth, int nHeight )
{
    /*int  n24 = (nWidth * 24 + 31)/32 * 4;	
    double coe_r = 0.45;
	double coe_g = 0.5;
	double coe_b = 1 - coe_r - coe_g;
	for( int i = 0; i < nHeight; i++ )
	{
        for( int j = 0; j < nWidth; j++ )
		{
			int   offset = i * n24 + 3 * j;
            BYTE  r = pSrc[ offset ];
			BYTE  g = pSrc[ offset + 1 ];
			BYTE  b = pSrc[ offset + 2 ];

            int   offsetDst = i * xWidth( nWidth ) + j;
			pDst[ offsetDst ] = ( coe_r * r + coe_g * g + coe_b * b );
		}
	}*/
}


BOOL bmpFileDirectory( CString strTitle, CString &  strdir )
{
	BROWSEINFO bi;  
	char dispname[2 * MAX_PATH], path[2 * MAX_PATH];  
	ITEMIDLIST * pidl;  
	
	bi.hwndOwner = 0;  
	bi.pidlRoot = 0;  
	bi.pszDisplayName = dispname;  
	//CString sTemp = _T( "请指定Bmp文件夹" );
	bi.lpszTitle = strTitle;//sTemp;  
	bi.ulFlags = BIF_RETURNONLYFSDIRS;  
	bi.lpfn = 0;  
	bi.lParam = 0;  
	bi.iImage = 0;  
	
	if (pidl = SHBrowseForFolder(&bi)) 
	{  
		SHGetPathFromIDList(pidl, path);
		strdir = path;
		return TRUE;
	}
	return FALSE;
}

void CDib::Clone( CDib* pDib)   //由pDib Clone
{
    if( pDib == NULL || !pDib->IsValid() )
		return;
	Close();

    if(!(m_hDrawDib=DrawDibOpen()))
		return;
	
	int nBmpFileHeaderSize = sizeof(BITMAPFILEHEADER);
	
	memcpy( (void*)&bmpFileHeader, &pDib->bmpFileHeader, nBmpFileHeaderSize );
	 
	m_pDib= (BYTE*)new char[bmpFileHeader.bfSize-nBmpFileHeaderSize];
	memcpy( m_pDib, pDib->m_pDib, bmpFileHeader.bfSize-nBmpFileHeaderSize);
	
	m_pDibBits=GetBits();
}

void CDib::SetBits( int width, int height, int pitch, const unsigned char* buf )
{
	Close();

    if(!(m_hDrawDib=DrawDibOpen()))
		return;
    //---------------------------------
	bmpFileHeader.bfType = *((WORD *)"BM");
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;

	int  nStep;// = x8Width(width);
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD);
	bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + nStep * height;
	 
     
	int nBmpFileHeaderSize = sizeof(BITMAPFILEHEADER);
	m_pDib= (BYTE*)new char[bmpFileHeader.bfSize-nBmpFileHeaderSize];
	//memset( m_pDib, 0, bmpFileHeader.bfSize-nBmpFileHeaderSize );
	for( int y = 0; y < height; y++ )
	{
	    memcpy( m_pDib + bmpFileHeader.bfOffBits -nBmpFileHeaderSize+ y*nStep, buf+y*pitch, width );
	}
    BITMAPINFOHEADER*  pInfo = (BITMAPINFOHEADER*)m_pDib;

	pInfo->biSize = sizeof(BITMAPINFOHEADER);
	pInfo->biWidth = width;
	pInfo->biHeight = height;
	pInfo->biPlanes = 1;
	pInfo->biBitCount = 8;
	pInfo->biCompression = 0;//BI_RGB;
	pInfo->biSizeImage = 0;
	pInfo->biXPelsPerMeter = 0;
	pInfo->biYPelsPerMeter = 0;
	pInfo->biClrUsed = 0;
	pInfo->biClrImportant = 0;
	
    RGBQUAD*  pRGB = (RGBQUAD*)(m_pDib+sizeof(BITMAPINFOHEADER));	 
	for( int i=0;i<256;i++)
	{
		pRGB[i].rgbBlue=i;
		pRGB[i].rgbGreen=i;
		pRGB[i].rgbRed=i;
		pRGB[i].rgbReserved=0;
	}

	m_pDibBits=GetBits();
}