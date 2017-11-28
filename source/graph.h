#pragma once


#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#define GAMEEXIT\
	SDL_FreeSurface(m_surface);\
	SDL_DestroyWindow( m_window );\
	SDL_DestroyRenderer(renderer);\
	SDL_Quit();exit(0);

extern SDL_Window * m_window;
extern SDL_Surface * m_surface;
extern TTF_Font * SansFont;
extern SDL_Renderer * renderer;
