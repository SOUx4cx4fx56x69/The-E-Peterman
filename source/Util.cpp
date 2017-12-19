#include"Util.hpp"

namespace Util{
    const char * 
    ReadFile(const char * path){
	FILE * file = fopen(path,"rb");
	if(!file) {
	fprintf(stderr,"Cannot get file %s\n",path);
	return(int)0;
	}
	fseek(file,0,SEEK_END);
	size_t sf = ftell(file);
	rewind(file);
	//printf("%d\n",sf);
        char * Text = (char*)malloc(sf+1);
	fread(Text, sf, 2, file);
        *(Text+sf+1)='\0';
	fclose(file);
	return Text;
   }
  SDL_Surface * 
  images::loadimage(const char * path, IMG_InitFlags flag,bool Transparent, 
	Uint8 r, Uint8 g, Uint8 b){
	   SDL_Surface * result;
           if(flag){
	    if( !( IMG_Init(flag) & flag ) ) {
		fprintf(stderr,"Error init SDL_image,%s\n",SDL_GetError());
		return 0;
	    }
		result=IMG_Load(path);
	   }
	   else
	    result = SDL_LoadBMP(path);
	   if(result == NULL) fprintf(stderr,"Error load image: %s\n",SDL_GetError());
	   SDL_Surface * optimizedResult = SDL_ConvertSurface(result, m_surface->format, 0);
	   if(!optimizedResult){
	    fprintf(stderr,"Error optimaze image:%s\n",SDL_GetError());
	    return result;
	  }
	  SDL_FreeSurface(result);
	  if ( Transparent )
		SDL_SetColorKey(optimizedResult, SDL_TRUE, SDL_MapRGB((*optimizedResult).format,r,g,b)); // SDL_TRUE to enable color key\
	SDL_FALSE to disable.

	  return optimizedResult;
 }
 void images::ClearImage(SDL_Surface * img){
	   SDL_FreeSurface(img);
	   img = 0;
 }
 void images::putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2,
		 unsigned int width, unsigned int height, SDL_Surface * dest, bool ignoreError){
        if(!ignoreError)
	 if(!img || !dest)
		 fprintf(stderr,"Bad dest/src surface in images::putimage\n"); 
	register SDL_Rect DestR, SrcR;
	DestR.x = x;
 	DestR.y = y;
	SrcR.x = x2;
	SrcR.y = y2;
	SrcR.w = width;
	SrcR.h = height;
	/*
	int SDL_BlitSurface(SDL_Surface*    src,
                    const SDL_Rect* srcrect,
                    SDL_Surface*    dst,
                    SDL_Rect*       dstrect)

	*/
	SDL_BlitSurface(img, &SrcR, m_surface, &DestR );


 }
	std::string Buttons::GetButton(void){
			SDL_Event e;
			while(1){
			SDL_PollEvent(&e);
			if(e.type == SDL_KEYDOWN){
			  if(e.key.keysym.scancode != SDL_GetScancodeFromKey(e.key.keysym.scancode)){
			   std::string btn = SDL_GetKeyName(e.key.keysym.sym);
			   e.key.keysym.scancode=(SDL_Scancode)0;
			   return btn;
			  }//if
			}//if
			}//while
	}//GetButton


namespace textures{
	namespace GL{

		GLuint LoadTexture(const char * path ){

    			ILuint imgID = 0;
			ILuint textureId;
			ilGenImages(1, &imgID);
			ilBindImage(imgID);
			ilLoadImage("textures/floor.tga");
			ilutRenderer(ILUT_OPENGL);  // Switch the renderer

			ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
		
			
			glGenTextures( 1, &textureId );
			glBindTexture( GL_TEXTURE_2D, textureId );
		
			glTexImage2D( GL_TEXTURE_2D, 
			0, 
			GL_RGBA,
			(GLuint)ilGetInteger( IL_IMAGE_WIDTH ),
 			(GLuint)ilGetInteger( IL_IMAGE_HEIGHT ),
			 0, GL_RGBA,
			 GL_UNSIGNED_BYTE, (GLuint*)ilGetData() );

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			ilDeleteImages  (1, &imgID);
			return textureId;
		}
	}
	namespace images{
		SDL_Texture * 
		LoadImageAsTexture(const char*path, IMG_InitFlags flags, SDL_Renderer * rend){
				SDL_Surface * tmpSurf = Util::images::loadimage(path,flags);
				SDL_Texture * ReturnTexture = SDL_CreateTextureFromSurface(rend,tmpSurf);
				SDL_FreeSurface(tmpSurf);
				return ReturnTexture;
		}//loadimage
		SDL_Texture * 
		LoadImageAsTexture(SDL_Surface * surf, SDL_Renderer * rend){
				SDL_Texture * ReturnTexture = SDL_CreateTextureFromSurface(rend,surf);
				return ReturnTexture;
		}//loadimage
	}//images
}//textures


/*
namespace sounds{
	bool Init(unsigned short bitrate, unsigned char channels, unsigned short chunk_size){
		if(Mix_OpenAudio(bitrate, MIX_DEFAULT_FORMAT, channels, chunk_size)==-1) return false;
		
	}
}
*/





}
