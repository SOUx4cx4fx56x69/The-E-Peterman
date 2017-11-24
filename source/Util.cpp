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
 void images::putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2,
		 unsigned int width, unsigned int height, SDL_Surface * dest){
	if(!img || !dest) fprintf(stderr,"Bad dest/src surface in images::putimage\n"); 
	SDL_Rect DestR, SrcR;
	DestR.x = x;
 	DestR.y = y;
	SrcR.x = x2;
	SrcR.y = y2;
	SrcR.w = width;
	SrcR.h = height;
	/*
	int SDL_BlitSurface(SDL_Surface*    src,
                    const SDL_Rect* srcrect,
                    SDL_Surface*    dst,
                    SDL_Rect*       dstrect)

	*/
	SDL_BlitSurface(img, &SrcR, m_surface, &DestR );


 }


}
