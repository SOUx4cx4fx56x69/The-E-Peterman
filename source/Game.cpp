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

static inline void DrawDoors(GLdouble x, GLdouble y, GLdouble z){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


		glTranslatef(x,y,z);

		glPushMatrix();
		glBegin(GL_QUADS);
		glEnd();
		glPopMatrix();
	
}

static inline void InitRoom(void){

	GLuint TextureID = Util::textures::GL::LoadTexture("textures/floor.tga");
	glBindTexture( GL_TEXTURE_2D, TextureID );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glPolygonMode(GL_FRONT, GL_LINE);

	glTranslatef(-0.5,-0.5,0);
	glScalef(1,1,1);

	glNewList(1, GL_COMPILE);
		glBegin(GL_QUADS);
			glColor3f(.33,.666,.9);
			//left
			/*
			The current texture coordinates are part of the data that is associated with each vertex and with the current raster position. Initially, the values for s, t, r, and q are (0, 0, 0, 1).

			*/
			//front
			glTexCoord3f( 0, 0, -1); 
			glVertex3f(0, 0, -1);

			glTexCoord3f( 1.0f, 0.0f, -1 );
			glVertex3f( 1.0f, 0.0f, -1);

			glTexCoord3f( 1.0f, 1.0f, 1 );
			glVertex3f(1.0f, 1.0f, 1);

			glTexCoord3f( 0.0f, 1.0f, 1 );
			glVertex3f(0.0f, 1.0f, 1);	

			//left
			glColor4ub(255,0,0,255);		
			glVertex3f(0, 1, 0);glTexCoord3f( -2, 1, 0 );	
			glVertex3f(-1, 2, 0);glTexCoord3f( 2, 2, 0 );
			glVertex3f(-1, -1, 1);glTexCoord3f( 2, -1, 1 );
			glVertex3f(0, 0, 1);glTexCoord3f( -2, 0, 1 );
	
			//bottom
		
			glColor3ub(0,0,255);

			glVertex3f(0, 0, -1); glTexCoord3f(0,0,-1);
			glVertex3f(1, 0, -1); glTexCoord3f(1,0,-1);

			glVertex3f(2, -1, 1); glTexCoord3f(2,-1,1);						
			glVertex3f(-1, -1, 1); glTexCoord3f(-1,-1,1);


			glColor3ub(0,255,0);
			
			//right
		       	glVertex3f(1, 0, 0); glTexCoord3f(0,0,1);
			glVertex3f(2, -1, 1); glTexCoord3f(1,-0,1);

			glVertex3f(2, 2, 1); glTexCoord3f(2,-1,1);
			glVertex3f(1, 1, 0); glTexCoord3f(-1,-1,0);		
				
		glEnd();
/*
		glBegin(GL_LINES);
						glColor4ub(255,0,0,255);			
						glVertex3f(0.0, 1, -1);

						glColor3ub(0,255,0);
						glVertex3f(-1, 2, 1);
			
						glColor3ub(255,0,255);
									
						glVertex3f(0, 0, -1);
						glVertex3f(-1, -1, 1);
						
						glVertex3f(1, 0, 0);
						glVertex3f(2, -1, 1);

						glVertex3f(1, 1, 0);
						glVertex3f(2, 2, 1);
						

			

		glEnd();
*/
	glEndList();
	

	ilDeleteImages  (1, &TextureID);

}
static inline void DrawTunnel(void){

	glMatrixMode(GL_PROJECTION);
	gluLookAt(
		1.0,1.0,0.0, // x,y,z eye  
		1.0,1.0,1.0, // Center 
		0,1,0);
	glMatrixMode(GL_MODELVIEW);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
		glCallList(1);
	glPopMatrix();
	glLoadIdentity();

}

void Drive::StartGame(void){

	//Light work which materials...

	GLdouble OffsetX=0, OffsetY=0, OffsetZ=0;
  	ilInit();
	if (ilGetError() != IL_NO_ERROR) 
	  fprintf (stderr,"Devil Error (ilInit)");
	

	ilClearColour( 255, 255, 255, 000 );

	SDL_GLContext glcontext = SDL_GL_CreateContext(m_window); // CreateOpenGL Context
	SDL_GL_SetSwapInterval(1);	//Vertical Sync
	
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); 
	glShadeModel(GL_SMOOTH);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	InitRoom();
	//glEnable(GL_LIGHTING);
			
//	SDL_SetRenderDrawColor(mrenderer, 30,40,30,20);
//	SDL_RenderClear(mrenderer);
//	SDL

	




	

	glClearColor(0.2, 0.2, 0.2, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glOrtho(0, w_w, h_w, 0, 2, -2);

	glMatrixMode(GL_MODELVIEW);

	//glViewport(x,y,w,h);

	glTranslatef(1,1,0);

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
