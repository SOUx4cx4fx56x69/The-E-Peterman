#include"Util.hpp"

namespace Util{

void *
images::loadimage(const char * path){
void * result;


{
FILE * img = fopen(path,"rb");
if(!img){
	exit(1);
}

fseek(img,0,SEEK_END);
size_t sfile = ftell(img);
rewind(img);
result = malloc(sfile);
fread(result, sfile, 1, img);
fclose(img);
}

//printf("%s\n",(char*)fresult);
return result;

}

void 
usseles::FillScreen(int color){
	setfillstyle(1,color);
	bar(0,0,getmaxx(),getmaxy());
}



}
