#include"graph.h"
#include"main.hpp"
#include"menu.hpp"


#include<stdlib.h>
#include<time.h>

SDL_Window * m_window;
SDL_Surface * m_surface;
SDL_Renderer * renderer;

TTF_Font * SansFont;

static inline void init_graph(void){
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) ERROR(SDL_GetError());
	m_window = SDL_CreateWindow( NAMEGAME, 30
						,30, 640, 480, SDL_WINDOW_SHOWN );
	renderer = SDL_CreateRenderer(m_window, 0 ,SDL_RENDERER_ACCELERATED);
	if(TTF_Init()) {
		fprintf(stderr,"TTF_Init error!\n");
	}
	SansFont=TTF_OpenFont("Sans.ttf", 24);
	if(!SansFont)ERROR(TTF_GetError());
	puts("Renderer init");
	
	/*
		const char* title, int x, int y, int w, int h, Uint32 flags
	*/
	if(!m_window)ERROR(SDL_GetError());

	// now get surface of window
	m_surface = SDL_GetWindowSurface( m_window );
}

#ifdef _WIN32 || _WIN64
int WinMain(int argc, char**arguments){
#else
int main(int argc, char ** arguments){
#endif
	srand(time(NULL));

	init_graph();



	StartMenu();


	GAMEEXIT;

}

