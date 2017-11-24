#include "graph.h"
#include"Util.hpp"
static const unsigned short count_menu_button=6;

inline void WriteMenu(unsigned char selected){


const char * menu[count_menu_button] = {"Game","Help","About","Settings","Exit","Check"}; //6

#define H 100
	
#undef H


}

void StartMenu(void){
	// fill screen
	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, 0xAD, 0xD8, 0xe6 ) );

	SDL_Surface * alock = Util::images::loadimage("textures/lock.bmp");

	Util::images::putimage(alock, 240, 150, 0, 0, 300, 400);


        //every time\
 	we are must update the surface of window
        SDL_UpdateWindowSurface( m_window ); // m_surface <-> m_window
	SDL_Delay( 2000 ); // 2000 microseconds / 1000 = 2second

}
