#include "graph.h"
#include "menu.hpp"
#include"Util.hpp"
#include<string>
#include<stdlib.h>
#include "Game.hpp"



static const unsigned short count_menu_button=5;



static void SettingsMenu(void){
bool menu=true;
SDL_Event e;
unsigned short selected = 0;


const unsigned int H = (h_w/GameDrive::CountGameKey);
const unsigned int CenterWidth = (w_w/2);

SDL_Surface * KeyMsg;
SDL_Surface * NameKeyMsg;
while(menu){
 SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, BACKGROUND ) );
 for(unsigned short i = GameDrive::CountGameKey+1;i--;){
	if(i == GameDrive::CountGameKey){
		if(selected==i)
		 KeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		  "Exit", MenuColor_Selected,w_w-30);
		else
		 KeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		  "Exit", MenuColor_NotSelected,w_w-30);
		Util::images::putimage(KeyMsg, CenterWidth+H/2, H+(H*i)/2 , 0, 0, w_w, h_w);
		SDL_FreeSurface(KeyMsg);
		continue;
	}

	NameKeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		 GameDrive::NameKeys[i].c_str(), DARKCOLOR,w_w-30);
	if(i==selected)
	 KeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		 GameDrive::GameKeys[i].c_str(), MenuColor_Selected,w_w-30);
	else
	 KeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		 GameDrive::GameKeys[i].c_str(), MenuColor_NotSelected,w_w-30);

	Util::images::putimage(KeyMsg, CenterWidth+H/2, H+(H*i)/2 , 0, 0, w_w, h_w);

	Util::images::putimage(NameKeyMsg, CenterWidth/2, H+(H*i)/2 , 0, 0, w_w, h_w);

	SDL_FreeSurface(KeyMsg);
	SDL_FreeSurface(NameKeyMsg);
	SDL_PollEvent(&e);
	}
	switch(e.type){ // event switch
		case SDL_QUIT:
			printf("Quit after %d ticks\n",e.quit.timestamp);
			GAMEEXIT;
			break;
		case SDL_KEYDOWN: 
		 if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			 std::string MenuKey = SDL_GetKeyName(e.key.keysym.sym);
			 printf("MENU KEY: %s\n", MenuKey.c_str());
			 if(MenuKey == "Escape") menu=false;
			 else if(MenuKey == "Return"){

				if(selected==GameDrive::CountGameKey) {
						char Tmp[(16)+1+(7)];
						FILE * file = fopen(KEYSPATH,"wb");
						for(unsigned char i = GameDrive::CountGameKey;i--;){
							sprintf(Tmp, "%s:%s\n",
							GameDrive::GameKeys[i].c_str(),
							GameDrive::NameKeys[i].c_str() );
							fwrite(Tmp, strlen(Tmp), 1, file);
						}
						fclose(file);
						menu=false;
						break;
					}

				SDL_Surface * tmpSurf = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		 			GameDrive::GameKeys[selected].c_str(), KEYCHANGINGCOLOR,w_w-30);

				Util::images::putimage(tmpSurf, 
				CenterWidth+H/2,
				H+(H*selected)/2 ,
			        0, 0, w_w, h_w);
				SDL_UpdateWindowSurface(m_window);

				SDL_FreeSurface(tmpSurf);
				std::string NewKey = Util::Buttons::GetButton();
				
				for(unsigned short i = GameDrive::CountGameKey;i--;){
					if (NewKey == GameDrive::GameKeys[i]) 
						NewKey = GameDrive::GameKeys[selected];
				}
				if(NewKey == "Escape") NewKey=GameDrive::GameKeys[selected];
				GameDrive::GameKeys[selected]=NewKey;// = Util::Buttons::GetButton();

			 }else if(MenuKey == "W" || MenuKey == "Up") {//elseif
				if(selected)
					 selected--;
			}else if(MenuKey == "S" || MenuKey == "Down"){
			 	if(selected < GameDrive::CountGameKey) 
					selected++;
			}//elseif
			
		  } //if (e.key...
			e.key.keysym.scancode=(SDL_Scancode)0;
			break;
		 default:
			break;
		}//switch
	
 
 SDL_UpdateWindowSurface(m_window);


}//while

}

static void StaticMenu(const char * textButton,const char * PathToFileTitle){
bool menu=true;
SDL_Event e;
PUTBUTTON(textButton);


const char * TextTitle = Util::ReadFile(PathToFileTitle);
puts(TextTitle);
SDL_Surface * TitleMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont, TextTitle, DARKCOLOR,w_w-30);
free((void*)TextTitle);

Util::images::putimage(TitleMsg, 170, (h_w/4), 0, 0, w_w, h_w);\
while(menu){
	SDL_UpdateWindowSurface(m_window);
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
			 if(MenuKey == "Return") menu=false;
			}
			e.key.keysym.scancode=(SDL_Scancode)0;
			break;
		default:
			break;
		}
}
SDL_FreeSurface(TitleMsg);


}

inline static void WriteHelp(void){
StaticMenu("|continue|","Menu/Files/Help.msg");
}inline static void WriteAbout(void){
StaticMenu("|continue|","Menu/Files/About.msg");
}inline static void WriteSettings(void){
SettingsMenu();
}


inline void WriteMenu(unsigned char selected){



const char * menu[count_menu_button] = {"Game","Help","About","Settings","Exit"}; //5


const unsigned int H = (w_w/count_menu_button);

//#define H 270 // TODO: from screen size.
//printf("%d %d\n",w_w,h_w);
//#define PADDING 100
const short PADDING = (w_w/2)-30;

TTF_Font * TitleFont = TTF_OpenFont("GameFont.ttf", 30);

//TTF_SetFontStyle(GameFont, TTF_STYLE_BOLD);

SDL_Surface * Title = TTF_RenderUTF8_Blended(TitleFont, "The-E-Peterman", Title_Color) ;

SDL_Surface * Text;
for(unsigned short i = count_menu_button;i--;){
 
 

 Util::images::putimage(Title, (w_w/2), H, 0, 0, w_w, h_w); // title
 if(i!=selected) 
   Text = TTF_RenderUTF8_Blended(GameFont, menu[i], MenuColor_NotSelected);
 else
  Text = TTF_RenderUTF8_Blended(GameFont, menu[i], MenuColor_Selected); 

 Util::images::putimage(Text, (H)+(H*i), PADDING+H, 0, 0, w_w, h_w);
 SDL_FreeSurface(Text);
}
SDL_FreeSurface(Title);
TTF_CloseFont(TitleFont);


//#undef PADDING
//#undef H


}

void * StartMenu(bool InGame){

	SDL_GetWindowSize(m_window, &h_w, &w_w);
	if(h_w<800 || w_w<600) {
		fprintf(stderr,"Minimal screen size 800x600\n");
		GAMEEXIT;
	}
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
   			 if(MenuKey == "A" || MenuKey == "Left"){
				if(MenuItem)
				 MenuItem--;
		    }else if(MenuKey == "D" || MenuKey == "Right"){
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

	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, BACKGROUND ) );
		
	Util::images::putimage(alock, (w_w/2)+40, (h_w/4), 0, 0, w_w, h_w);
    //every time\
 	we are must update the surface of window
 	WriteMenu(MenuItem);
    SDL_UpdateWindowSurface( m_window ); // m_surface <-> m_window
	SDL_Delay( 1 ); // 2000 microseconds / 1000 = 2second
	}
	Util::images::ClearImage(alock);
	
	//{"Game","Help","About","Settings","Exit"}
	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, BACKGROUND ) );
	switch(MenuItem){	
		case Game:
			return (void*)0;
			break;
		case Help:
			WriteHelp();
			break;
		case About:
			WriteAbout();
			break;
		case Settings:
			WriteSettings();
			break;
		case Exit:
			GAMEEXIT;
			break;
		default:
			fprintf(stderr,"Default %d\n",MenuItem);
			break;	
	}
	StartMenu(InGame);

}
