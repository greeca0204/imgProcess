#include "stdafx.h"
#include "smooth.h"

void Smooth3X3( const unsigned char* srcBuf, int w, int h, int step,
			   unsigned char* dstBuf, int w1, int h1, int step1,
			   float ref[], Pt  pt[] )
{
    for( int y = 1; y < h-1; y++ )
	{
		for( int x = 1; x < w-1; x++ )
		{
			float  sum = 0;
			float  neof = 0;
			for( int k = 0; k < 9; k++ )
			{
				sum += srcBuf[(y+pt[k].y)*step+(x+pt[k].x)]*ref[k];
				neof += ref[k];
			}
			sum /= neof;
			dstBuf[y*step1+x] = sum;
		}
	}
}


void Lap3X3( const unsigned char* srcBuf, int w, int h, int step,
			   unsigned char* dstBuf, int w1, int h1, int step1,
			   float ref[], Pt  pt[] )
{
    for( int y = 1; y < h-1; y++ )
	{
		for( int x = 1; x < w-1; x++ )
		{
			float  sum = 0;
			//float  neof = 0;
			for( int k = 0; k < 9; k++ )
			{
				sum += srcBuf[(y+pt[k].y)*step+(x+pt[k].x)]*ref[k];
				//neof += ref[k];
			}
			//---sum /= neof;
			//sum*=10;
			if( sum < 0 )
				sum = 0;
			if( sum > 255 )
				sum = 255;
			dstBuf[y*step1+x] = sum;
		}
	}
}

