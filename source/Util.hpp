#include"graph.h"
#include<stdlib.h>



namespace Util{
	namespace images{
		SDL_Surface * loadimage(const char*);
		void ClearImage(SDL_Surface*);
		void putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2, // from x2 image, from y2 image
		 unsigned int width, unsigned int height, SDL_Surface * dest=m_surface);
	}
}
