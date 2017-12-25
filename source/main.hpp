#pragma once
#if defined(_WIN32) || defined(_WIN64)
 #include<stdio.h>
#endif



#define ERROR_(str){\
	fprintf(stderr,"%s\n",str);\
	exit(3);\
}
