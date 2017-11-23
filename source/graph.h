#pragma once
#include <windows.h>
#include <graphics.h>

#define INITMAX const int maxx=getmaxx(),maxy=getmaxy();

#define ENTER_BUTTON 13

// for check library, not need.
#define LINESRAND\
	for(unsigned short i=255;i--;){\
		setcolor(rand()%16);\
       	 	line(rand()%320, rand()%320, getmaxx(), getmaxy());\
	}
