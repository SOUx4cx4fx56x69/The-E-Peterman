#pragma once


#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#define GAMEEXIT\
	SDL_FreeSurface(m_surface);\
	SDL_DestroyWindow( m_window );\
	SDL_DestroyRenderer(renderer);\
	SDL_Quit();\
	exit(0);

#define PUTBUTTON(text){\
SDL_Surface * Button = TTF_RenderUTF8_Blended(GameFont, text, {41,255,42});\
Util::images::putimage(Button, (w_w/2), (h_w/2), 0, 0, w_w, h_w);\
SDL_FreeSurface(Button);\
}

extern SDL_Window * m_window;
extern SDL_Surface * m_surface;
extern TTF_Font * GameFont;
extern SDL_Renderer * renderer;
extern int h_w , w_w; // height of window, width of window
