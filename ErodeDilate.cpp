#include "stdafx.h"

#include "EdrodeDilate.h"

void gErode( unsigned char* srcBuf, int w, int h, int step, unsigned char* dstBuf, int step1, POINT pt[], int n )
{
     for( int y = 0; y < h; y++ )
	 {
		 for( int x = 0; x < w; x++ )
		 {
			 int Tag = 1;
			 for( int k = 0; k < n; k++ )
			 {
                 if( srcBuf[(y+pt[k].y)*step+x+pt[k].x] == 0 )
				 {
					 Tag =0;
					 break;
				 }
			 }
			 
			 dstBuf[y*step1+x] = Tag*255;
		 }
	 }

}


void gDilate( unsigned char* srcBuf, int w, int h, int step, unsigned char* dstBuf, int step1, POINT pt[], int n )
{
     for( int y = 0; y < h; y++ )
	 {
		 for( int x = 0; x < w; x++ )
		 {
			 if( srcBuf[y*step+x] )
			 {
			     for( int k = 0; k < n; k++ )
				 {
					 dstBuf[(y+pt[k].y)*step1+x+pt[k].x] = 255;
				 }
			 }
			 //dstBuf[y*step1+x] = Tag*255;
		 }
	 }

}
