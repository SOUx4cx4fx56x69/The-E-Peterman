#include "graph.h"
#include "menu.hpp"
#include"Util.hpp"
#include<string>
#include<stdlib.h>
#include "Game.hpp"

#if defined(_WIN32) || defined(_WIN64)
	#include<string.h>
#endif

#define MOUSECHECK(event, type, buttons_rect,i)\
				event.type.x  >= buttons_rect[i].x  &&  \
				event.type.x <= buttons_rect[i].x + buttons_rect[i].w\
				&& \
				event.type.y  >= buttons_rect[i].y &&\
				event.type.y <= buttons_rect[i].y + buttons_rect[i].h


#define SETTINGKEY\
				if(selected==GameDrive::CountGameKey) {\
						char Tmp[(16)+1+(7)];\
						FILE * file = fopen(KEYSPATH,"wb");\
						for(unsigned char i = GameDrive::CountGameKey;i--;){\
							sprintf(Tmp, "%s:%s\n",\
							GameDrive::GameKeys[i].c_str(),\
							GameDrive::NameKeys[i].c_str() );\
							fwrite(Tmp, strlen(Tmp), 1, file);\
						}\
						fclose(file);\
						menu=false;\
						break;\
					}\
				\
				SDL_Surface * tmpSurf = TTF_RenderUTF8_Blended_Wrapped(GameFont,\
		 			GameDrive::GameKeys[selected].c_str(), KEYCHANGINGCOLOR,w_w-30);\
				\
				Util::images::putimage(tmpSurf, \
                               	ButtonsCoords[selected].x,\
                                H+(H*selected)/4 ,\
			        0, 0, w_w, h_w);\
				SDL_UpdateWindowSurface(m_window);\
				\
				SDL_FreeSurface(tmpSurf);\
				std::string NewKey = Util::Buttons::GetButton();\
				\
				for(unsigned short i = GameDrive::CountGameKey;i--;){\
					if (NewKey == GameDrive::GameKeys[i]) \
						NewKey = GameDrive::GameKeys[selected];\
				}\
				if(NewKey == "Escape") NewKey=GameDrive::GameKeys[selected];\
				GameDrive::GameKeys[selected]=NewKey;// = Util::Buttons::GetButton();



static const unsigned short count_menu_button=5;
//static SDL_Point * ButtonsCoords;
static SDL_Rect * ButtonsCoords;
//static int mouse_x, mouse_y;

static void SettingsMenu(void){
bool menu=true;
bool ButtonsInited = false;
SDL_Event e;
unsigned short selected = 0;

ButtonsCoords = new SDL_Rect[GameDrive::CountGameKey+1];

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
		  "Exit", MenuColor_Selected,w_w);
		else
		 KeyMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont,
		  "Exit", MenuColor_NotSelected,w_w);

		if(!ButtonsInited){
			ButtonsCoords[i].x = (w_w/2+KeyMsg->w);
			ButtonsCoords[i].y = H+(H*i)/4;
			ButtonsCoords[i].h = KeyMsg->h;
			ButtonsCoords[i].w = KeyMsg->w;
		}
                Util::images::putimage(KeyMsg, ButtonsCoords[i].x, ButtonsCoords[i].y , 0, 0, w_w, h_w);
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

	if(!ButtonsInited){
			ButtonsCoords[i].x = w_w-KeyMsg->w;
			ButtonsCoords[i].y = H+(H*i)/4;
			ButtonsCoords[i].h = KeyMsg->h;
			ButtonsCoords[i].w = KeyMsg->w;
	}

        Util::images::putimage(KeyMsg, ButtonsCoords[i].x, ButtonsCoords[i].y , 0, 0, w_w, h_w);

        Util::images::putimage(NameKeyMsg, (w_w-NameKeyMsg->w)/4, ButtonsCoords[i].y , 0, 0, w_w, h_w);

	SDL_FreeSurface(KeyMsg);
	SDL_FreeSurface(NameKeyMsg);
	
	}
	SDL_PollEvent(&e);
	if(!ButtonsInited)
		ButtonsInited=true;
	switch(e.type){ // event switch
		case SDL_QUIT:
			printf("Quit after %d ticks\n",e.quit.timestamp);
			GAMEEXIT;
			break;
		case SDL_MOUSEMOTION:
			for(unsigned short i = GameDrive::CountGameKey+1;i--;){
				if( MOUSECHECK(e, motion, ButtonsCoords, i) ){
					selected = i;
					break;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			for(unsigned short i = GameDrive::CountGameKey+1;i--;){

				if( MOUSECHECK(e, motion, ButtonsCoords, i) ){
					selected = i;
					SETTINGKEY;
					break;
				}
			}
		case SDL_KEYDOWN: 
		 if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			 std::string MenuKey = SDL_GetKeyName(e.key.keysym.sym);
			 printf("MENU KEY: %s\n", MenuKey.c_str());
			 if(MenuKey == "Escape") menu=false;
			 else if(MenuKey == "Return"){
				SETTINGKEY;
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
delete ButtonsCoords;
ButtonsCoords=0;

}

static void StaticMenu(const char * textButton,const char * PathToFileTitle){
bool menu=true;
SDL_Event e;

ButtonsCoords = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
PUTBUTTON(textButton, ButtonsCoords);




const char * TextTitle = Util::ReadFile(PathToFileTitle);
puts(TextTitle);
SDL_Surface * TitleMsg = TTF_RenderUTF8_Blended_Wrapped(GameFont, TextTitle, DARKCOLOR,w_w);
free((void*)TextTitle);

Util::images::putimage(TitleMsg, (w_w+w_w/10)-TitleMsg->w, (h_w/4), 0, 0, w_w, h_w);\
while(menu){
	SDL_UpdateWindowSurface(m_window);
	SDL_PollEvent(&e); // event	
	switch(e.type){ // event switch
		case SDL_MOUSEBUTTONDOWN:
			if( MOUSECHECK(e, button, ButtonsCoords,0) )
			 	menu=false;
				break;
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

free(ButtonsCoords);
ButtonsCoords=0;


}

static void SetLevel(void){
unsigned char menuItem = 0;
SDL_Surface * Text;
SDL_Event e;
bool ButtonsInited = false, menu=true;
const unsigned int H = (h_w/GameDrive::DifficultyCount);

ButtonsCoords = new SDL_Rect[GameDrive::DifficultyCount];


while(menu){

	for(unsigned char i = GameDrive::DifficultyCount; i--;){
		if( i == menuItem)	
			Text = TTF_RenderUTF8_Blended_Wrapped(GameFont, 
				GameDrive::difficulty[i].c_str(), MenuColor_Selected,w_w);
		else
			Text = TTF_RenderUTF8_Blended_Wrapped(GameFont, 
				GameDrive::difficulty[i].c_str(), MenuColor_NotSelected, w_w);
		if(!ButtonsInited){
			ButtonsCoords[i].x = w_w/2-Text->w;
			ButtonsCoords[i].y = H+(H*i)/4;
			ButtonsCoords[i].h = Text->h;
			ButtonsCoords[i].w = Text->w;
		}
		Util::images::putimage(Text, ButtonsCoords[i].x, ButtonsCoords[i].y , 0, 0, w_w, h_w);
		SDL_FreeSurface(Text);
	}
	SDL_UpdateWindowSurface(m_window);
	SDL_PollEvent(&e); // event	
	switch(e.type){ // event switch
		case SDL_MOUSEMOTION:
			for(unsigned short i = GameDrive::DifficultyCount;i--;){
				if( MOUSECHECK(e, motion, ButtonsCoords, i) ){
					menuItem = i;
					break;
				}
			}
			break;
		case SDL_KEYDOWN: 
		 if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			 std::string MenuKey = SDL_GetKeyName(e.key.keysym.sym);
			 printf("MENU KEY: %s\n", MenuKey.c_str());
			 if(MenuKey == "Escape") menu=false;
			 else if(MenuKey == "Return"){
				GameDrive::dif=menuItem;
				menu=false;
				break;
			 }else if(MenuKey == "W" || MenuKey == "Up") {//elseif
				if(menuItem)
					 menuItem--;
			}else if(MenuKey == "S" || MenuKey == "Down"){
			 	if(menuItem < GameDrive::DifficultyCount-1) 
					menuItem++;
			}//elseif
			
		  } //if (e.key...
			e.key.keysym.scancode=(SDL_Scancode)0;
			break;
		case SDL_MOUSEBUTTONDOWN:
			for(unsigned short i = GameDrive::DifficultyCount;i--;){
					if( MOUSECHECK(e, motion, ButtonsCoords, i) ){
						menu=false;
						break;
					}
				}
			break;
		case SDL_QUIT:
			printf("Quit after %d ticks\n",e.quit.timestamp);
			GAMEEXIT;
			break;
		default:
			break;
		}
}
ButtonsCoords=0;


      


}

inline static void WriteHelp(void){
StaticMenu("|continue|","Menu/Files/Help.msg");
}inline static void WriteAbout(void){
StaticMenu("|continue|","Menu/Files/About.msg");
}inline static void WriteSettings(void){
SettingsMenu();
}



static inline void WriteMenu(unsigned char selected, bool inGame){
bool ButtonsInited = true;




const char * menu[count_menu_button] = { inGame ? "Continue" : "Game" ,"Help","About","Settings","Exit"}; //5


if(!ButtonsCoords){
	ButtonsInited=false;
	ButtonsCoords=(SDL_Rect*)malloc(sizeof(SDL_Rect)*count_menu_button);
}


const unsigned int H = ( w_w/count_menu_button+1 );

//#define H 270 // TODO: from screen size.
//printf("%d %d\n",w_w,h_w);
//#define PADDING 100
const short PADDING = (w_w/2);

TTF_Font * TitleFont = TTF_OpenFont("GameFont.ttf", 30);

//TTF_SetFontStyle(GameFont, TTF_STYLE_BOLD);

SDL_Surface * Title = TTF_RenderUTF8_Blended(TitleFont, NAMEGAME, Title_Color) ;
Util::images::putimage(Title,  (w_w/4)+Title->w, H, 0, 0, w_w, h_w); // title

SDL_Surface * Text;

for(unsigned short i = count_menu_button;i--;){ 
 if(i!=selected) 
   Text = TTF_RenderUTF8_Blended(GameFont, menu[i], MenuColor_NotSelected);
 else
  Text = TTF_RenderUTF8_Blended(GameFont, menu[i], MenuColor_Selected); 

if(!ButtonsInited){
		ButtonsCoords[i].x = (w_w/4)-(Text->w)+(H*i);
		ButtonsCoords[i].y = PADDING+H;
		ButtonsCoords[i].w = Text->w;
		ButtonsCoords[i].h = Text->h;
}

 Util::images::putimage(Text, (w_w/4)-(Text->w)+(H*i), PADDING+H, 0, 0, w_w, h_w);
 SDL_FreeSurface(Text);
}
SDL_FreeSurface(Title);
TTF_CloseFont(TitleFont);


//#undef PADDING
//#undef H


}

void * StartMenu(bool InGame){

	bool menuActive=true;
	SDL_Event e;
	unsigned char MenuItem = 0;
	
	SDL_Surface * alock = Util::images::loadimage("textures/lock.png", IMG_INIT_PNG, true); // 

	while( menuActive ){ 
	
	
	SDL_PollEvent(&e); // event	
	switch(e.type){ // event switch
		case SDL_MOUSEMOTION:
			//SDL_GetMouseState(&mouse_x, &mouse_y);
			for(unsigned short i = count_menu_button;i--;){
				if( MOUSECHECK(e, motion, ButtonsCoords, i) )
					MenuItem = i;	
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			for(unsigned short i = count_menu_button;i--;){
				if( MOUSECHECK(e, button, ButtonsCoords, i) ){
					menuActive=false;
				//	printf("Clicked %s\n",menu[i]);
				}
			}
			break;
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
				menuActive=false;
			}
		}
			e.key.keysym.scancode=(SDL_Scancode)0;
			break;
		default:
			break;
	}//End Switch event
	
	// fill screen

	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, BACKGROUND ) );
		
        Util::images::putimage(alock,  (w_w/3)+alock->w, (h_w/4), 0, 0, alock->w, alock->h);
    //every time\
 	we are must update the surface of window
 	WriteMenu(MenuItem, InGame);
    	SDL_UpdateWindowSurface( m_window ); // m_surface <-> m_window
	SDL_Delay( 1 ); // 2000 microseconds / 1000 = 2second
	}

	free(ButtonsCoords);
	ButtonsCoords=0;

	Util::images::ClearImage(alock);
	
	//{"Game","Help","About","Settings","Exit"}
	SDL_FillRect( m_surface, NULL, SDL_MapRGB( m_surface->format, BACKGROUND ) );
	switch(MenuItem){	
		case Game:
			if(!InGame)
			 SetLevel();
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

#undef MOUSECHECK
