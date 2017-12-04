#include"graph.h"
#include"main.hpp"
#include"menu.hpp"
#include"Game.hpp"
#include<stdlib.h>
#include<time.h>

SDL_Window * m_window;
SDL_Surface * m_surface;
SDL_Renderer * renderer;
int h_w , w_w;
TTF_Font * GameFont;
unsigned short SizeFont;

static inline void init_graph(void){
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) ERROR(SDL_GetError());
	m_window = SDL_CreateWindow( NAMEGAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP

 );
	renderer = SDL_CreateRenderer(m_window, 0 ,SDL_RENDERER_ACCELERATED);
	if(TTF_Init()) {
		fprintf(stderr,"TTF_Init error!\n");
	}
	SDL_GetWindowSize(m_window, &h_w, &w_w);
	if(h_w<800 || w_w<600) {
		fprintf(stderr,"Minimal screen size 800x600\n");
		GAMEEXIT;
	}
        printf("%d x %d\n",h_w,w_w);
	SizeFont = ((h_w+w_w)/100);
        GameFont=TTF_OpenFont("GameFont.ttf", SizeFont );
	if(!GameFont)ERROR(TTF_GetError());
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

	GameDrive::Drive game = GameDrive::Drive();
	

	StartMenu(false);
	game.StartGame();

	GAMEEXIT;

}

