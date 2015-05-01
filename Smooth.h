#ifndef _SMOOTHHHHHHH
#define _SMOOTHHHHHHH

struct Pt
{
	int x, y;
};
void Smooth3X3( const unsigned char* srcBuf, int w, int h, int step,
			   unsigned char* dstBuf, int w1, int h1, int step1,
			   float ref[], Pt  pt[] );



void Lap3X3( const unsigned char* srcBuf, int w, int h, int step,
			   unsigned char* dstBuf, int w1, int h1, int step1,
			   float ref[], Pt  pt[] );

#endif