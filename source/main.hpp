#pragma once
#ifdef _WIN32 || _WIN64
 #include<stdio.h>
#endif



#define ERROR(str){\
fprintf(stderr,"%s\n",str);\
exit(3);\
}
