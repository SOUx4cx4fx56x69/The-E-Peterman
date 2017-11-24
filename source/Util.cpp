#include"Util.hpp"

#define ERRORREAD(path){\
	fprintf(stderr,"CANNOT READ %s!\n",path);\
	free(result);\
	fclose(img);\
	return 0;\
}

namespace Util{

void *
images::loadimage(const char * path){
void * result;


{
FILE * img = fopen(path,"rb");
if(!img)
	exit(3);


fseek(img,0,SEEK_END);
size_t sfile = ftell(img);
rewind(img);
result = malloc(sfile);

if(!result) exit(3);

if(!fread(result, sfile, 1, img)) ERRORREAD(path);
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
