#include"graph.h"
#ifdef _WIN32 || _WIN64
 #include<stdlib.h>
#endif
#include<stdio.h>
#include <SDL2/SDL_image.h>
#include<string>


namespace Util{
	extern const char * ReadFile(const char * path);
	namespace images{
		SDL_Surface * loadimage(const char*, IMG_InitFlags flags=(IMG_InitFlags)0);
		/*
		typedef enum
		{
   		 IMG_INIT_JPG = 0x00000001,
   		 IMG_INIT_PNG = 0x00000002,
 		   IMG_INIT_TIF = 0x00000004
		} IMG_InitFlags;
		*/
		void ClearImage(SDL_Surface*);
		void putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2, // from x2 image, from y2 image
		 unsigned int width, unsigned int height, SDL_Surface * dest=m_surface,bool ignoreError=true);
	}//images

	namespace Buttons{
		std::string GetButton(void);
	}//Buttons

}//Util
