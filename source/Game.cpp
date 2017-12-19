#include "Game.hpp"
#include"Util.hpp"
#include"graph.h"



#include <GL/gl.h>
#include <GL/glu.h>



#include<unistd.h>

namespace GameDrive{

typedef enum{
Top, Left, Bottom, Right, Action, Jump
}GameKeysEnum;
const std::string NameKeys[CountGameKey]{
"Forward",
"Left",
"Down",
"Right",
"Action",
"Jump"
};

std::string GameKeys[CountGameKey] = {
"W", // Top
"A", // Left
"S", // Bottom
"D", // Right
"E", // Action
"Space" // Jump
};

Drive::Drive(void){
	this->InitKeys();
}

void Drive::InitKeys(void){
	const char * Keys = Util::ReadFile(KEYSPATH);
	//printf("%s\n",Keys);
	void * fKeys = (void *)Keys;
	std::string KeyValue, KeyName;
	bool IsValue = true;
	while(*Keys){
		if(*Keys == '\n'){
		//	printf("%s : %s\n",KeyValue.c_str(),KeyName.c_str());
			*Keys++;
			IsValue=true;
			for(unsigned char i = CountGameKey-1;i--;){
				if(NameKeys[i]==KeyName)
					GameKeys[i]=KeyValue;
			}
			KeyValue="";
			KeyName="";
			continue;
		}
		if(*Keys==':'){*Keys++;IsValue=false;continue;}
		if(IsValue)
		 KeyValue += *Keys++;//operator overloading thx
		else
		  KeyName += *Keys++;
	}

	free(fKeys);
}

void Drive::StartGame(void){

	SDL_GLContext glcontext = SDL_GL_CreateContext(m_window); // CreateOpenGL Context
	SDL_GL_SetSwapInterval(1);	//Vertical Sync

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
			
//	SDL_SetRenderDrawColor(mrenderer, 30,40,30,20);
//	SDL_RenderClear(mrenderer);
//	SDL

	






	glClearColor(0, 0.3, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glOrtho(0, w_w, h_w, 0, 2, -2);

	glMatrixMode(GL_MODELVIEW);

	for(unsigned int i = 0;i<100;i++){
		
		
		//glLoadIdentity();
		glColor3f(0.3,0.3,1);
		glLineWidth(0.666);

		glTranslatef(0, i, 0);
		
		glPushMatrix();
		glBegin(GL_LINES);
			glVertex2f(0,0);
			glVertex2f(w_w,0);
		glEnd();
		glPopMatrix();
		glFlush();
	}

	SDL_RenderPresent(mrenderer);

	GLenum glError = glGetError();
	if(glError != GL_NO_ERROR) printf("OpenGL error: %s\n", gluErrorString(glError));

	
	
//	SDL_GL_SwapWindow(m_window); // Swap Window
	SDL_Delay(1000);
	SDL_GL_DeleteContext(glcontext); //Delete Context
	
}

}
