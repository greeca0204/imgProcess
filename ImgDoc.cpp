// ImgDoc.cpp : implementation of the CImgDoc class
//

#include "stdafx.h"
#include "Img.h"

#include "ImgDoc.h"
#include <assert.h>
#include "EdrodeDilate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//		gErode( m_dib.GetBits() + step + 1,  w-2, h-2, step, buf+step1+1, step1, pt, 4 );

/////////////////////////////////////////////////////////////////////////////
// CImgDoc

IMPLEMENT_DYNCREATE(CImgDoc, CDocument)

BEGIN_MESSAGE_MAP(CImgDoc, CDocument)
	//{{AFX_MSG_MAP(CImgDoc)
	ON_COMMAND(ID_READBMP, OnReadbmp)
	ON_COMMAND(ID_FRAY, OnFray)
	ON_COMMAND(ID_HIST, OnHist)
	ON_COMMAND(ID_D, OnD)
	ON_COMMAND(ID_P, OnP)
	ON_COMMAND(ID_OTSU, OnOtsu)
	ON_COMMAND(ID_Lap, OnLap)
	ON_COMMAND(ID_EXP, OnExp)
	ON_COMMAND(ID_ERODE, OnErode)
	ON_COMMAND(ID_DILATE, OnDilate)
	ON_COMMAND(ID_FILL, OnFill)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_GRAYERODE, OnGrayerode)
	ON_COMMAND(ID_HIT, OnHit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgDoc construction/destruction

CImgDoc::CImgDoc()
{
	// TODO: add one-time construction code here

}

CImgDoc::~CImgDoc()
{
}

BOOL CImgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImgDoc serialization

void CImgDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImgDoc diagnostics

#ifdef _DEBUG
void CImgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImgDoc commands
void CImgDoc::Draw( CDC* pDC)
{
    if( m_dib.IsValid() )
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4; //step pitch
		//int  k = w%4;



        for( int y = 0; y < h; y++ )
		{
			for( int x = 0; x < w; x++ )
			{
				int  v = m_dib.GetBits()[y*w1+x];
				pDC->SetPixel( x+10, h-y+10, RGB( v, v, v ));
			}
		}

	}
}

void CImgDoc::OnReadbmp() 
{
	// TODO: Add your command handler code here
	CDib::SelectBmpFile(&m_dib );
	UpdateAllViews(NULL);
}

void CImgDoc::OnFray() 
{
	// TODO: Add your command handler code here
	if( m_dib.IsValid())
	{
       float  a = 30;
	   float  b = 200;
	   float  c = 50;
	   float  d = 80;

		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4;

       for( int y = 0; y < h; y++ )
	   {
		   for( int x = 0; x < w; x++ )
		   {
			   if(m_dib.GetBits()[y*w1+x]>=a && m_dib.GetBits()[y*w1+x] <= b ) 
                   m_dib.GetBits()[y*w1+x] =  (m_dib.GetBits()[y*w1+x]-a)/(b-a)*(d-c)+c;
		   }
	   }
	   UpdateAllViews( NULL );

	   m_dib.Save("e:\\Img\\123.bmp" );
	}
}

void CImgDoc::OnHist() 
{
	// TODO: Add your command handler code here
	int   nHist[256]; //nHist[0], nHist[1]
    //for( int i = 0; i < sizeof(nHsit)/sizeof(nHist[0]); i++ )
	//{
	//	nHist[i] =0;
	//}
	memset(nHist, 0, sizeof(nHist ) );

		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4;

       for( int y = 0; y < h; y++ )
	   {
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   nHist[v]++;
		   }
	   }
}

void CImgDoc::OnD() 
{
	// TODO: Add your command handler code here

	int   nPsHist[256]; // 
    //for( int i = 0; i < sizeof(nHsit)/sizeof(nHist[0]); i++ )
	//{
	//	nHist[i] =0;
	//}
	memset(nPsHist, 0, sizeof(nPsHist ) );

		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4;
       int y;
       for( y = 0; y < h; y++ )
	   {
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   nPsHist[v]++;
		   }
	   }
       //------
	   float   fPtHist = ((w*h)/256.0);///(w*h);// = 1/256.0;
       int  nTable[256]; //nTable[0] 0->nTable[0]
        //nTable[1]    1->nTable[1]
  
       for( int i = 0; i < 256; i++ )
	   {
		   float sum = 0;
           for( int j = 0; j <= i; j++ )
		   {
			   sum += nPsHist[j];
		   }
           nTable[i] = sum/fPtHist;




	   }
       for( y = 0; y < h; y++ )
	   {
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   m_dib.GetBits()[y*w1+x] = nTable[v];
		   }
	   }
	   UpdateAllViews( NULL );
}

void CImgDoc::OnP() 
{
    float   per = 0.15;
	if( m_dib.IsValid())
	{
		assert( per < 1 );
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4;
        int  dot = w*h*per;

		int   nPsHist[256]; // 
		memset(nPsHist, 0, sizeof(nPsHist ) );
		int y;
		for( y = 0; y < h; y++ )
		{
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   nPsHist[v]++;
		   }
		}
		int  v1 = 0;
		int  sum = 0;
		while ( 1 )
		{
			sum += nPsHist[v1];
			if( sum >=dot )
			{
				break;
			}
			v1++;
		}
        
		for( y = 0; y < h; y++ )
		{
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   if( v <=v1 )  
				   m_dib.GetBits()[y*w1+x] = 0xff;
			   else
				   m_dib.GetBits()[y*w1+x]=0 ;
		   }
		}
        UpdateAllViews(NULL); 


	}
}

void CImgDoc::OnOtsu() 
{
	//TODO: Add your command handler code here
	if( m_dib.IsValid())
	{
		//assert( per < 1 );
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  w1 = (w*8+31)/32*4;
		//if( n&0x1 )
        //int  dot = w*h*per;
		int   nHist[256]; // 
		memset(nHist, 0, sizeof(nHist ) );
		int y;
		for( y = 0; y < h; y++ )
		{
		   for( int x = 0; x < w; x++ )
		   {
			   int v = m_dib.GetBits()[y*w1+x];
			   nHist[v]++;
		   }
		}
        float m = 0;
        int  i, j;
		for( i = 0; i < 256; i++ )
		{
			m += nHist[i]*i;
		}
		m /= ( w*h);
        //-------
		int  v = 0;
		float fMax = 0;
		for( i = 0; i < 256; i++ )
		{
			//pa ma
			int Pa = 0;
			float ma = 0;
            for( j = 0; j <=i; j++ )
			{
			   Pa += nHist[j];
			   ma += j*nHist[j];
			}
			if( Pa == 0 )
               continue;
            ma /= Pa; 			

			//pb mb
			int Pb = 0;
			float mb = 0;
            for( j = i+1; j <256; j++ )
			{
			   Pb += nHist[j];
			   mb += j*nHist[j];
			}
			if( Pb == 0 )
               continue;
            mb /= Pb; 			
            //==================
			float f = Pa*(ma-m)*(ma-m) + Pb*(mb-m)*(mb-m);
            if( f > fMax )
			{
				fMax = f;
				v = i;
			}
		}
        // 
		for( y = 0; y < h; y++ )
		{
		   for( int x = 0; x < w; x++ )
		   {
			   int v1 = m_dib.GetBits()[y*w1+x];
			   if( v1 <= v ) 
				   m_dib.GetBits()[y*w1+x] = 0xff;
			   else
				   m_dib.GetBits()[y*w1+x] = 0;
		   }
		}
        UpdateAllViews(NULL);
	}
}

void CImgDoc::OnLap() 
{
	//TODO: Add your command handler code here
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
         
        unsigned char* buf = new unsigned char[h*step];
        int y;
		for( y = 1; y < h-1; y++ )
		{
			for( int x = 1; x < w-1; x++ )
			{
				int v = (5*m_dib.GetBits()[y*step+x] -
                    m_dib.GetBits()[y*step+x-1]-m_dib.GetBits()[y*step+x+1]-
					m_dib.GetBits()[(y-1)*step+x]-m_dib.GetBits()[(y+1)*step+x]);
                if( v < 0 )
					v = 0;
				if( v > 255 )
					v = 255;
				buf[y*step+x] = v;
			}
		}
        for( y = 1; y < h-1; y++ )
		{
			memcpy( m_dib.GetBits()+y*step+1, buf+y*step+1, w-2 );
		}
		UpdateAllViews(NULL);
    }
}

void CImgDoc::OnExp() 
{
	// TODO: Add your command handler code here
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
         
        int  w1 = 1.75*w;
		int  h1 = 0.65*h;
		int  step1 = w1;
        unsigned char* buf = new unsigned char[h1*step1];
        /*-----------------------------
        x = (w-1.0)/(w1-1)*x1;
		y = (h-1.0)/(h1-1)*y1;
        */
		float fx = (w-1.0)/(w1-1);
		float fy = (h-1.0)/(h1-1);
        for( int y = 0; y < h1; y++ )
		{
			for( int x = 0; x < w1; x++ )
			{
                float X0 = fx*x;  //1.2  1.8  
				float Y0 = fy*y;
                int  x1 = X0;  //1
                int  y1 = Y0;
				float a = X0-x1;
				float b = Y0-y1;
				float a1 = m_dib.GetBits()[y1*step+x1] +
					a*(float(m_dib.GetBits()[y1*step+x1+1]) - m_dib.GetBits()[y1*step+x1] );



				//
			//	buf[y*step1+x] = ?;//
			}
		}
		CDib::SaveImg8( "e:\\123.bmp", buf, w1, h1, step1 );
        delete []buf;
	}	
}


void CImgDoc::OnErode() 
{
	// int _INT64  long long 
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
   
        
		int  w1 = w;
		int  h1 = h;
		int  step1 = w1;
        unsigned char* buf = new unsigned char[step1*h1];
		
        
        POINT   pt[25];
		pt[0].x = 0; pt[0].y = -1;
		pt[1].x = 1; pt[1].y = 0;
		pt[2].x = 0; pt[2].y = 1;
		pt[3].x = -1; pt[3].y = 0;

		//const unsigned char* buf12 = m_dib.GetBits() + 2*step + 2;
		//gErode( buf12,  w-4, h-4, step, buf+2*step1+2, step1, pt, 25 );
      
		CDib::SaveImg8( "e:\\123.bmp", buf, w1, h1, step1 );
		delete []buf;
	}
	


}

void CImgDoc::OnDilate() 
{
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
        
		int  w1 = w;
		int  h1 = h;
		int  step1 = w1;
        unsigned char* buf = new unsigned char[step1*h1];
        
        POINT   pt[4];
		pt[0].x = -1; pt[0].y = 0;
		pt[1].x = 0; pt[1].y = -1;
		pt[2].x = 1; pt[2].y = 0;
		pt[3].x = 0; pt[3].y = 1;

		memset( buf, 0, step1*h1 );
		gDilate( m_dib.GetBits() + step + 1,  w-2, h-2, step, buf+step1+1, step1, pt, 4 );
      
		CDib::SaveImg8( "e:\\dilate.bmp", buf, w1, h1, step1 );
		delete []buf;
	}
	
	
}

void CImgDoc::OnFill() 
{
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
        
		int  w1 = w;
		int  h1 = h;
		int  step1 = w1;
        unsigned char* buf1 = new unsigned char[step1*h1];
	    int x, y;
		for( y = 0; y < h; y++ )
		{
			for( x = 0;x < w; x++ )
			{
				buf1[y*step1+x] = 255-m_dib.GetBits()[y*step+x];
			}
		}
        POINT   pt[5];
		pt[0].x = -1; pt[0].y = 0;
		pt[1].x = 0; pt[1].y = -1;
		pt[2].x = 1; pt[2].y = 0;
		pt[3].x = 0; pt[3].y = 1;
        pt[4].x =pt[4].y = 0;


		int  w2 = w;
		int  h2 = h;
		int  step2 = w2;
        unsigned char* buf2 = new unsigned char[step2*h2];
        memset( buf2, 0, step2*h2 );
		buf2[(h2-23)*step2+92] = 255;

		int  w3 = w;
		int  h3 = h;
		int  step3 = w3;
        unsigned char* buf3 = new unsigned char[step3*h3];
        memset( buf3, 0, step3*h3 );
		CDib::SaveImg8( "e:\\buf2.bmp", buf2, w2, h2, step2 );
		CDib::SaveImg8( "e:\\buf1.bmp", buf1, w1, h1, step1 );
	
		
		
		while( 1 )
		{
			//---
			int  n1 = 0;
			for( y = 0; y < h; y++ )
			{
				for( x = 0; x < w; x++ )
				{
				    if( buf2[y*step2+x] )
						n1++;
				}
			}

		    gDilate( buf2 + step2 + 1,  w2-2, h2-2, step2, buf3+step3+1, step3, pt, 5 );
            //buf3 and buf1 => buf2
			for( y = 0; y < h; y++ )
			{
				for( x = 0; x < w; x++ )
				{
					buf2[y*step2+x] = ( buf1[y*step1+x] & buf3[y*step3+x] );
				}
			}
			int  n2 = 0;
			for( y = 0; y < h; y++ )
			{
				for( x = 0; x < w; x++ )
				{
				    if( buf2[y*step2+x] )
						n2++;
				}
			}
            if( n1 == n2 )
				break;

		}
        //---buf2 
          
		CDib::SaveImg8( "e:\\Fill.bmp", buf2, w2, h2, step2 );

        delete []buf2;
		delete []buf3;
		delete []buf1;
	}
}

void CImgDoc::OnOpen() 
{
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
        //---- Erode  Dialte
		int  w1 = w;
		int  h1 = h;
		int  step1 = w1;
        unsigned char* buf1 = new unsigned char[step1*h1];
		memset( buf1, 0, step1*h1 );
        POINT   pt[9];
        for( int k = 0; k < 9; k++)
		{
			pt[k].x = k%3-1;
			pt[k].y = k/3-1;
		}
		gErode( m_dib.GetBits()+step+1,  w-2, h-2, step, buf1+step1+1, step1, pt, 9 );
      
		CDib::SaveImg8( "e:\\Erode.bmp", buf1, w1, h1, step1 );
		//delete []buf;
        //buf1 => dilate ==> m_dib.GetBits()

		memset( m_dib.GetBits(), 0, h*step );
		gDilate( buf1+step1+1,  w-2, h-2, step1, m_dib.GetBits()+step+1, step, pt, 9 );
        
		CDib::SaveImg8( "e:\\Open", m_dib.GetBits(),w, h, step );
        delete []buf1;
		UpdateAllViews(NULL);
	}	
}

void CImgDoc::OnGrayerode() 
{
	// TODO: Add your command handler code here
	
}

void CImgDoc::OnHit() 
{
	if( m_dib.IsValid())
	{
		int  w = m_dib.GetWidth();
		int  h = m_dib.GetHeight();
		int  step = (w*8+31)/32*4;
        
        POINT   pt[9];
        pt[0].x = -2; pt[0].y = 0;
		pt[1].x = -1; pt[1].y = 0;
		pt[2].x = 0; pt[2].y = -2;
		pt[3].x = 0; pt[3].y = -1;
		pt[4].x = 0; pt[4].y = 0;
		pt[5].x = 1; pt[5].y = 0;
		pt[6].x = 2; pt[6].y = 0;
		pt[7].x = 0; pt[7].y = 1;
		pt[8].x = 0; pt[8].y = 2;

		//---- Erode  Dialte
		int  w1 = w;
		int  h1 = h;
		int  step1 = w1;
        unsigned char* buf1 = new unsigned char[step1*h1];
		memset( buf1, 0, step1*h1 );
        gErode( m_dib.GetBits()+ 2*step+2, w-4, h-4, step,
			buf1+2*step1+2, step1, pt, 9 );

		CDib::SaveImg8( "e:\\1.bmp", buf1, w1, h1, step1 );
        ///step2;

        POINT   pt1[16];
        pt1[0].x = -2; pt1[0].y = -2;
		pt1[1].x = -1; pt1[1].y = -2;
		pt1[2].x = -2; pt1[2].y = -1;
		pt1[3].x = -1; pt1[3].y = -1;
		pt1[4].x = -2; pt1[4].y = 1;
		pt1[5].x = -1; pt1[5].y = 1;
		pt1[6].x = -2; pt1[6].y = 2;
		pt1[7].x = -1; pt1[7].y = 2;
		pt1[8].x = 1; pt1[8].y = -2;
		pt1[9].x = 2; pt1[9].y = -2;
		pt1[10].x = 1; pt1[10].y = -1;
		pt1[11].x = 2; pt1[11].y = -1;
		pt1[12].x = 1; pt1[12].y = 1;
		pt1[13].x = 2; pt1[13].y = 1;
		pt1[14].x = 1; pt1[14].y = 2;
		pt1[15].x = 2; pt1[15].y = 2;
    
		
        int x, y;
		for( y = 0; y < h; y++ )
		{
			for( x = 0; x < w; x++ )
			{
				m_dib.GetBits()[y*step+x] = 255-m_dib.GetBits()[y*step+x];
			}
		}
        
		int  w2 = w;
		int  h2 = h;
		int  step2 = w1;
        unsigned char* buf2 = new unsigned char[step2*h2];
		memset( buf2, 0, step2*h2 );
        gErode( m_dib.GetBits()+ 2*step+2, w-4, h-4, step,
			buf2+2*step2+2, step2, pt1, 16 );
		CDib::SaveImg8( "e:\\2.bmp", buf2, w2, h2, step2 );

		for( y = 0; y < h; y++ )
		{
			for( x = 0; x < w; x++ )
			{
				buf2[y*step2+x] = buf2[y*step2+x] & buf1[y*step1+x];
			}
		}
		CDib::SaveImg8( "e:\\3.bmp", buf2, w2, h2, step2 );

        delete []buf2;
		delete []buf1;
	}
}
