#include"graph.h"
#include"main.hpp"
#include"menu.hpp"


#include<stdlib.h>
#include<time.h>

static inline void init_graph(void){
	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) ERROR(SDL_GetError());
	m_window = SDL_CreateWindow( NAMEGAME, 0
						,0, 640, 480, SDL_WINDOW_SHOWN );
	/*
		const char* title, int x, int y, int w, int h, Uint32 flags
	*/
	if(!m_window)ERROR(SDL_GetError());

	// now get surface of window
	m_surface = SDL_GetWindowSurface( m_window );
}


int main(int argCount,char**arguments){
	srand(time(NULL));

	init_graph();

	// fill screen
	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, 0xAD, 0xD8, 0xe6 ) );

        //every time\
 	we are must update the surface of window
        SDL_UpdateWindowSurface( m_window ); // m_surface <-> m_window

	SDL_Delay( 2000 ); // 2000 microseconds / 1000 = 2second

	SDL_DestroyWindow( m_window ); // free memory \
	and close SDL subsystems
	SDL_Quit();




	StartMenu();

}
