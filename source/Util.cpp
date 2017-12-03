#include"Util.hpp"

namespace Util{

  SDL_Surface * 
  images::loadimage(const char * path, IMG_InitFlags flag){
	   SDL_Surface * result;
           if(flag){
	    if( !( IMG_Init(flag) & flag ) ) {
		fprintf(stderr,"Error init SDL_image,%s\n",SDL_GetError());
		return 0;
	    }
		result=IMG_Load(path);
	   }
	   else
	    result = SDL_LoadBMP(path);
	   if(result == NULL) fprintf(stderr,"Error load image: %s\n",SDL_GetError());
	   SDL_Surface * optimizedResult = SDL_ConvertSurface(result, m_surface->format, 0);
	   if(!optimizedResult){
	    fprintf(stderr,"Error optimaze image:%s\n",SDL_GetError());
	    return result;
	  }
	  SDL_FreeSurface(result);
	  return optimizedResult;
 }
 void images::ClearImage(SDL_Surface * img){
	   SDL_FreeSurface(img);
	   img = 0;
 }
 void images::putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2,
		 unsigned int width, unsigned int height, SDL_Surface * dest, bool ignoreError){
        if(!ignoreError)
	 if(!img || !dest)
		 fprintf(stderr,"Bad dest/src surface in images::putimage\n"); 
	register SDL_Rect DestR, SrcR;
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
	std::string Buttons::GetButton(void){
			SDL_Event e;
			while(1){
			SDL_PollEvent(&e);
			if(e.type == SDL_KEYDOWN){
			  if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			   std::string btn = SDL_GetKeyName(e.key.keysym.sym);
			   e.key.keysym.scancode=(SDL_Scancode)0;
			   return btn;
			  }//if
			}//if
			}//while
	}//GetButton


}
