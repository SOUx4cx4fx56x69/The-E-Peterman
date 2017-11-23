#include "graph.h"
#include"Util.hpp"
static const unsigned short count_menu_button=6;

inline void WriteMenu(unsigned char selected){

INITMAX;
const char * menu[count_menu_button] = {"Game","Help","About","Settings","Exit","Check"}; //6

#define H 100

settextstyle(EUROPEAN_FONT, 0, 3);

setcolor(BLUE);
outtextxy((maxx/2)-120,H-60,(char*)"The E-Peterman");

setcolor(YELLOW);


for(unsigned char counter=count_menu_button-1;counter--;){
	printf("%d %d\n",selected,counter);
	if(selected == counter){
		setcolor(GREEN);
		outtextxy((maxx/2)-60,(counter*30)+H,(char*)menu[counter]);
		setcolor(YELLOW);
	}else
	 outtextxy((maxx/2)-60,(counter*30)+H,(char*)menu[counter]);
}	
#undef H



}

void StartMenu(void){

void * alock = Util::images::loadimage("textures/lock.bmp");
//printf("%d %d\n",getmaxx(),getmaxy());
char ch;
int selectm __attribute__((mode(QI)))=0;
while(1){
setbkcolor(BROWN);
Util::usseles::FillScreen(BROWN);
puts("Start copy");

//putimage(360,360,alock,COPY_PUT); // error(360,360) just for test
WriteMenu(selectm);
ch = getch();
if(!ch) ch = getch();
printf("%d\n",ch);

switch(ch){
case KEY_UP: // TOP BUTTON
 if(selectm)selectm--;
 break;
case KEY_DOWN:
 if(selectm+2<count_menu_button) selectm++;
 break;
case ENTER_BUTTON:
default:
 break;
}




}




}
