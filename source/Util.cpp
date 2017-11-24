#include"Util.hpp"

namespace Util{

  SDL_Surface * 
  images::loadimage(const char * path){
	   SDL_Surface * result = SDL_LoadBMP(path);
	   if(result == NULL) fprintf(stderr,"Error load image: %s\n",SDL_GetError());
	   return result;
 }
 void images::ClearImage(SDL_Surface * img){
	   SDL_FreeSurface(img);
	   img = 0;
 }


}
