#include"graph.h"
#if defined(_WIN32) || defined(_WIN64)
 #include<stdlib.h>
#endif
#include<stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include<string>


namespace Util{
	extern const char * ReadFile(const char * path);
	namespace images{
		SDL_Surface * loadimage(const char*, IMG_InitFlags flags=(IMG_InitFlags)0, bool Transparent=false, Uint8 r=0xFF, Uint8 g=0xFF, Uint8 b = 0xFF); // 4228250625 Uint32 SI
		/*
		typedef enum
		{
   		 IMG_INIT_JPG = 0x00000001,
   		 IMG_INIT_PNG = 0x00000002,
 		   IMG_INIT_TIF = 0x00000004
		} IMG_InitFlags;
		*/
		void ClearImage(SDL_Surface*);
		void putimage(SDL_Surface * img,
		unsigned int x,unsigned int y,
		unsigned int x2, unsigned int y2, // from x2 image, from y2 image
		 unsigned int width, unsigned int height, SDL_Surface * dest=m_surface,bool ignoreError=true);
	}//images
/*
	namespace sounds{
		template <typename Type>  Type OpenFile(const char * path, bool asmusic=true);

		void Play(Mix_Music * mus);
		void Play(Mix_Chunk * mus);

		void Halt(Mix_Music * mus);
		void Pause(Mix_Music * mus);
		bool Init(unsigned short bitrate=22050, unsigned char channels=2, unsigned short chunk_size=1024);
	}
*/
	namespace Buttons{
		std::string GetButton(void);
	}//Buttons
	namespace textures{
		namespace images{
			SDL_Texture * LoadImageAsTexture(const char*, IMG_InitFlags flags=(IMG_InitFlags)0, SDL_Renderer * rend=mrenderer );
			SDL_Texture * LoadImageAsTexture(SDL_Surface * surf, SDL_Renderer * rend=mrenderer);
		}
	}

}//Util
