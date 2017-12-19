#include "Game.hpp"
#include"Util.hpp"
#include"graph.h"



#include <GL/gl.h>
#include <GL/glu.h>



#include<unistd.h>

namespace GameDrive{




const std::string difficulty[DifficultyCount]{
"noob","normal","hard"
};

unsigned char dif;

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

static void DrawTunnel(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(.33,.666,.9);
		//left
		glVertex3f(0,0,-1);
		glVertex3f(0,h_w,-1);
		glVertex3f(w_w,0,1);
		glVertex3f(w_w,h_w,1);

		//bottom
		glColor3f(0.1,0.5,0.4);
		glVertex3f(0, h_w, -2); 
		glVertex3f(w_w, h_w, -2); 
		glVertex3f(w_w, h_w, 2); 
		glVertex3f(0, 0, 2);
		
		//right
		glColor3f(0.32,0.42,.32);
		glVertex3f(w_w,h_w,-2); // right bottom FAR
		glVertex3f(w_w,0,-2); // right top FAR
		glVertex3f(0,h_w,2); // right top near
		glVertex3f(w_w,h_w,0); // right bottom near

		//top
		glColor3f(0.31,0.32,.32);
		glVertex3f(0,0,-2);
		glVertex3f(w_w,0,-2);
		glVertex3f(0,h_w,2);
		glVertex3f(w_w,h_w,2);
		
		//glLoadIdentity();
		//Left 
	glEnd();
	glPopMatrix();
}

void Drive::StartGame(void){

	SDL_GLContext glcontext = SDL_GL_CreateContext(m_window); // CreateOpenGL Context
	SDL_GL_SetSwapInterval(1);	//Vertical Sync

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glEnable(GL_LIGHTING);
			
//	SDL_SetRenderDrawColor(mrenderer, 30,40,30,20);
//	SDL_RenderClear(mrenderer);
//	SDL

	




	

	glClearColor(0.7, 0.6, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glOrtho(0, w_w, h_w, 0, 2, -2);

	glMatrixMode(GL_MODELVIEW);

	//glViewport(x,y,w,h);

	
	DrawTunnel();
	

	//glTranslated(-w_w,0,0);
	SDL_RenderPresent(mrenderer);

	GLenum glError = glGetError();
	if(glError != GL_NO_ERROR) printf("OpenGL error: %s\n", gluErrorString(glError));

	
	
//	SDL_GL_SwapWindow(m_window); // Swap Window

	Util::Buttons::GetButton();
	SDL_Delay(1000);
	SDL_GL_DeleteContext(glcontext); //Delete Context
	
}

}
