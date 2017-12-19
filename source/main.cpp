#include"graph.h"
#include"main.hpp"
#include"menu.hpp"
#include"Game.hpp"
#include"Util.hpp"



#include<stdlib.h>

#include<time.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window * m_window;
SDL_Surface * m_surface;
SDL_Renderer * mrenderer;
int h_w , w_w;
TTF_Font * GameFont;
unsigned short SizeFont;

static inline void init_graph(void){
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 ) ERROR(SDL_GetError());
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

	m_window = SDL_CreateWindow( NAMEGAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL 

 );
	mrenderer = SDL_CreateRenderer(m_window, -1 ,SDL_RENDERER_ACCELERATED);
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

#if defined(_WIN32) || defined(_WIN64)
int WinMain(int argc, char**arguments){
#else
int main(int argc, char ** arguments){
#endif
//	pthread_t CursorThread;
	srand(time(NULL));
	
	init_graph();
	//void * (*CursorThread)(void*);
	SDL_Surface * cursor = Util::images::loadimage("textures/cursor.png", IMG_INIT_PNG);
	if(cursor){
		SDL_Cursor * curs=SDL_CreateColorCursor(cursor, 0, 0);
		if(curs) SDL_SetCursor(curs);
		else fprintf(stderr,"Cursor error: %s\n",SDL_GetError());
	}
	SDL_FreeSurface(cursor);
	GameDrive::Drive game = GameDrive::Drive();


	StartMenu(false);
	game.StartGame();

	GAMEEXIT;

}

