#pragma once
static SDL_Window * m_window;
static SDL_Surface * m_surface;

#define NAMEGAME "The-E-Peterman"

#define ERROR(str){\
fprintf(stderr,"%s\n",str);\
exit(3);\
}
