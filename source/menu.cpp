#include "graph.h"
#include"Util.hpp"
#include<string>

static const unsigned short count_menu_button=6;

inline void WriteMenu(unsigned char selected){



const char * menu[count_menu_button] = {"Game","Help","About","Settings","Exit","Check"}; //6

const SDL_Color MenuColor_NotSelected = {255,149,29}; // RGB
const SDL_Color MenuColor_Selected = {123,215,68}; // RGB
const SDL_Color Title_Color = {0,0,255};

#define H 45
#define PADDING 70
for(unsigned short i = count_menu_button;i--;){
 SDL_Surface * Text;
 SDL_Surface * Title = TTF_RenderUTF8_Blended(SansFont, "The-E-Peterman", Title_Color) ;
 Util::images::putimage(Title, 230, PADDING-40, 0, 0, 300, 400);
 if(i!=selected) 
   Text = TTF_RenderUTF8_Blended(SansFont, menu[i], MenuColor_NotSelected);
 else
  Text = TTF_RenderUTF8_Blended(SansFont, menu[i], MenuColor_Selected); 
 Util::images::putimage(Text, 270, PADDING + i*H, 0, 0, 300, 400);
 SDL_FreeSurface(Text);
 SDL_FreeSurface(Title);

}


#undef PADDING
#undef H


}

void StartMenu(void){
	bool menu=true;
	SDL_Event e;
	unsigned char MenuItem = 0;
	
	
	
	SDL_Surface * alock = Util::images::loadimage("textures/lock.png", IMG_INIT_PNG); // 

	while( menu ){ 
	
	
	SDL_PollEvent(&e); // event	
	switch(e.type){ // event switch
		case SDL_QUIT:
			printf("Quit after %d ticks\n",e.quit.timestamp);
			GAMEEXIT;
			break;
		case SDL_KEYDOWN: 
			if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			 std::string MenuKey = SDL_GetKeyName(e.key.keysym.sym);
			 printf("MENU KEY: %s\n", MenuKey.c_str());
   			 if(MenuKey == "W" || MenuKey == "Up"){
				if(MenuItem)
				 MenuItem--;
		    }else if(MenuKey == "S" || MenuKey == "Down"){
			  if(MenuItem < count_menu_button-1) MenuItem++;
			}else if(MenuKey == "Return"){
				menu=false;
			}
		}
			e.key.keysym.scancode=(SDL_Scancode)0;
			break;
		default:
			break;
	}//End Switch event
	
	// fill screen
	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, 0x2D, 0x30, 0x3B ) );
	Util::images::putimage(alock, 255, 150, 0, 0, 300, 400);
    //every time\
 	we are must update the surface of window
 	WriteMenu(MenuItem);
    SDL_UpdateWindowSurface( m_window ); // m_surface <-> m_window
	SDL_Delay( 1 ); // 2000 microseconds / 1000 = 2second
	}
	Util::images::ClearImage(alock);
	

	switch(MenuItem){	
		Game:
			break;
		Help:
			break;
		default:
			break;	
	}

}
