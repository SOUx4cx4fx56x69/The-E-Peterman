#include"Util.hpp"

namespace Util{

void *
images::loadimage(const char * path){
char * result;
void * fresult;


{
FILE * img = fopen(path,"rb");
if(!img){
	exit(1);
}

fseek(img,0,SEEK_END);
unsigned long sfile = ftell(img);
rewind(img);
result = (char*)malloc(sfile);

fresult=result;

for(sfile;sfile--;){
	*(result++) = getc(img);
	//printf("%c\n",*result);
	
}

}

printf("%s\n",(char*)fresult);
return fresult;

}

void 
usseles::FillScreen(int color){
	setfillstyle(1,color);
	bar(0,0,getmaxx(),getmaxy());
}



}
