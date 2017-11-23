#include"graph.h"
#include"main.hpp"
#include"menu.hpp"


#include<stdlib.h>
#include<time.h>


int main(int argCount,char**arguments){

	srand(time(NULL));
	initgraph((int*)&gd,(int*)&gm,(char*)"");


	StartMenu();

	closegraph();
}
