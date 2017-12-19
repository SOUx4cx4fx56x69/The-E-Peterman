#pragma once


#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>


#define GAMEEXIT\
	SDL_FreeSurface(m_surface);\
	SDL_DestroyWindow( m_window );\
	SDL_DestroyRenderer(mrenderer);\
	TTF_CloseFont(GameFont);\
	TTF_Quit();\
	SDL_Quit();\
	exit(0);

#define PUTBUTTON(text, Coords){\
SDL_Surface * Button = TTF_RenderUTF8_Blended(GameFont, text, {41,255,42});\
Coords[0].x=(w_w/2)+( SizeFont+FONTPAD*strlen(text) )/2;\
Coords[0].y=(h_w/2);\
Coords[0].h=Button->h;\
Coords[0].w=Button->w;\
Util::images::putimage(Button, Coords[0].x, Coords[0].y, 0, 0, w_w, h_w);\
SDL_FreeSurface(Button);\
}
#define NAMEGAME "The-E-Peterman"

#define FONTPAD 10

extern SDL_Window * m_window;
extern SDL_Surface * m_surface;
extern TTF_Font * GameFont;
extern SDL_Renderer * mrenderer;
extern int h_w , w_w; // height of window, width of window
extern unsigned short SizeFont;
extern SDL_Renderer * mrenderer;
