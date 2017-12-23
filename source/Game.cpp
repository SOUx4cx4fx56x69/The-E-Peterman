#include "Game.hpp"
#include"Util.hpp"
#include"graph.h"



#include <GL/gl.h>
#include <GL/glu.h>








#include<unistd.h>

#define REVERSESTRING(str){\
	char * tmpStr = malloc(GameDrive::Crypto::Rotor::_strlen_(str));\
	void * ftmpStr=tmpStr;\
	void *fStr = str;\
	while(*str) *tmpStr++=*str++;\
	str = fStr;\
	while(tmpStr != ftmpStr) *str++=*tmpStr--;\
	free(tmpStr);\
}

#define COTENATION(array, phrase, sizeArray){\
	if(sizeArray < GameDrive::Crypto::Rotor::_strlen_(phrase) > sizeArray){\
		sizeArray += GameDrive::Crypto::Rotor::_strlen_(phrase) - sizeArray;\
		array = (char*)realloc(array, sizeArray);\
	}\
		{\
		register unsigned long i = 0;\
		puts(phrase);\
		while(*array) *array++;\
		while(phrase[i]) *array++ = (phrase[i++]);\
		}\
}

namespace GameDrive{



namespace Crypto{
	namespace Numbers{
		typedef unsigned long long ull;
		char * convertNumberToPhrases(unsigned long long number){
			unsigned long alloced, used=0;
		
			alloced = number/10 + 1;

			char * result = (char*)malloc(sizeof(ull)*alloced);
			void * fresult = result;
			register unsigned char num;
			while(number){
				if( used + 1 > alloced ){
					result = (char*)realloc(result, alloced+1);
					alloced+=1;
				}
				num = number % 10;
				switch(num){
					case 0:
						COTENATION(result, "zero", alloced);
						break;
					case 1:
						COTENATION(result, "one", alloced);
						break;
					case 2:
						COTENATION(result, "two", alloced);
						break;
					case 3:
						COTENATION(result, "three", alloced);
						break;
					case 4:
						COTENATION(result, "four", alloced);
						break;
					case 5:
						COTENATION(result, "five", alloced);
						break;
					case 6:
						COTENATION(result, "six", alloced);
						break;
					case 7:
						COTENATION(result, "seven", alloced);
						break;
					case 8:
						COTENATION(result, "eight", alloced);
						break;
					case 9:
						COTENATION(result, "nine", alloced);
						break;
					default:
						break;
				}
				used++;
				number/=10;

			}
			while(*result)*result++;
			*result='\0';
			return (char*)fresult;
		}
	};

	namespace Rotor{
		unsigned long _strlen_( const char * p){
			unsigned long r = 0;
			while(*p++) r++;
			return r;
		}

		template <class T> void shuffle(T * arr, unsigned int index0, unsigned int index1){
				//printf("%d %d\n",index0,index1);
				T tmp = arr[index0];
				arr[index0]=arr[index1];
				arr[index1]=tmp;
				//printf("Shuffle: %s\n", arr);
		}


		char * RotoPhrase(const char * what, unsigned char count){
			unsigned long sphrase = _strlen_(what);
			char * result = (char*)malloc( sphrase+1 ); // char 1 byte, then sizeof don't need
			void * fresult = result;
			while( *what )
				if(*what == ' ') {*what++;continue;}
				else *result++=*what++;// Copy full.
			*result++='\0';
			result=(char*)fresult;
			register unsigned int tmpi;		
			printf("Copy: %s\n",result);	
			for(count;count--;){
				tmpi= rand()%sphrase + 1;
				if( !result[tmpi]  ){
					count++;
					continue;
				}
				if(tmpi - 1 < 0)
				 shuffle<char>(result, tmpi, tmpi+1);
				else if(tmpi + 1 < sphrase)
				 shuffle<char>(result, tmpi, tmpi-1);	
				else
				{
					count++;
					continue;
				}
			}
			return result;
			
		}
	};
};



namespace FreeType{
FT_Face InitFace(const char * fontName, unsigned short height){
 FT_Library library;
 if (FT_Init_FreeType( &library ))
	{
		fprintf(stderr, "Error with FreeType init library\n");
		GAMEEXIT;
	}
 	FT_Face face;
	if (FT_New_Face( library, fontName, 0, &face )) {
		fprintf(stderr, "Error with FreeType New Face\n");
		GAMEEXIT;
	}
	return face;
}

};




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


		glLoadIdentity();
		
		glMatrixMode(GL_PROJECTION);

		glTranslatef(x,y,z);
		glMatrixMode(GL_MODELVIEW);
		




		glPushMatrix();
			glCallList(2);
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
	
	//Room
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
	//Doors
	glNewList(2,GL_COMPILE);
		glBegin(GL_QUADS);
		glColor3ub(0,0,0);
			
			//first Door

			glVertex3f(0,0,0);
			glVertex3f(0.25,0,1);
			glVertex3f(0.25,-0.5,1);
			glVertex3f(0,-0.5,1);
			
			//Two Door

			glVertex3f(1.0, 0, 1);
			glVertex3f(0.8, 0, 1);

			glVertex3f(0.8, -0.8, 1);
			glVertex3f(1, -1, 1);
			
			// three door
			glVertex3f(-0.8, 0, 1);
			glVertex3f(-0.8, -0.8, 1);

			glVertex3f(-1.2, -1.2, 1);
			glVertex3f(-1.2, 0, 1);

		glEnd();
		glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 1.0);
			//first Door
			glVertex3f(0.0, 0, 0);
			glVertex3f(0.25, 0, 1);
			
			glVertex3f(0.25, 0, 1);
			glVertex3f(0.25, -0.5, 1);
			
			glVertex3f(0, 0, 1);
			glVertex3f(0, -0.5, 1);


			//two Door
			glVertex3f(1.0, 0, 1);
			glVertex3f(0.8, 0, 1);

			glVertex3f(0.8, 0, 1);
			glVertex3f(0.8, -0.8, 1);
			//three door
			glVertex3f(-0.8, 0, 1);
			glVertex3f(-0.8, -0.8, 1);

			glVertex3f(-0.8, 0, 1);
			glVertex3f(-1.2, 0, 1);
			
			
		glEnd();
	glEndList();

	//Book
	glNewList(3,GL_COMPILE);
		glBegin(GL_LINES);
			glVertex3f(-0, -0.75, 1);
			glVertex3f(0.3, -0.75, 1);
			
			glVertex3f(0.3,-0.75,1);
			glVertex3f(0.3,-0.65,1);
		glEnd();

		glBegin(GL_QUADS);
		
			glVertex3f(-0, -0.65, 1);
			glVertex3f(0, -0.75, 1);

			glVertex3f(0.3, -0.75, 1);			
			glVertex3f(0.3,-0.65,1);

		glEnd();


			

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	

	DrawDoors(1,1,0);
	glCallList(3);
	glDisable(GL_BLEND);
/*
	SDL_Surface * CheckText = TTF_RenderUTF8_Blended(GameFont, "Check", {255,0,0});
	SDL_Texture * Check_Text = SDL_CreateTextureFromSurface(mrenderer,CheckText);
	SDL_FreeSurface(CheckText);

	SDL_Rect Coords = {w_w/2,h_w/2,255,255};	
	SDL_RenderCopy(mrenderer, Check_Text, NULL, &Coords);
*/
//	SDL_BlitSurface(m_surface, NULL, CheckText, NULL);

	

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
