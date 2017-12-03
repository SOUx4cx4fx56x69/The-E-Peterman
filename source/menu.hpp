#define DARKCOLOR {120,110,100}
#define BACKGROUND 0X0C,0X05,0X19
#define KEYCHANGINGCOLOR {200,200,200}
void StartMenu(bool InGame);
const SDL_Color MenuColor_NotSelected = {178,94,28}; // RGB
const SDL_Color MenuColor_Selected = {41,255,42}; // RGB
const SDL_Color Title_Color = {44, 97, 217};

typedef enum{
	Game=0, Help, About, Settings, Exit
}MenuElements;
