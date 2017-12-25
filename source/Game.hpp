#pragma once
#include<string>
#include <sstream>

#define KEYSPATH "Settings/Keys.bnd"
#define ROTORMOVING 255
#define MOVINGGAME 2
#define MAXNUMBERROTOR 1000

//#ifndef _WIN32
/*#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
*/
typedef unsigned long long ull;

namespace GameDrive{

const unsigned char CountGameKey = 6;
const unsigned char DifficultyCount = 3;

typedef enum{
Top, Left, Bottom, Right, Action, Jump
}GameKeysEnum;




extern std::string GameKeys[CountGameKey];
extern const std::string NameKeys[CountGameKey];
extern const std::string difficulty[DifficultyCount];
extern unsigned char dif;




class Drive{
private:
	ull * rooms;
	void * lRooms;
	void InitKeys(void);
	ull WinRoom;
	char * Phrase;
	ull BossPass;
	bool BossRoom(void);
protected:
	void OpenShipher(void);
	void InitIL();
	std::stringstream numToStr(ull num, unsigned char element);
public:
	void InitLevels(void);
	void StartGame(void);
	Drive(void);

};

/*
namespace FreeType{
	FT_Face InitFace(const char * fontName, unsigned short height);

};
*/
namespace Crypto{
	namespace Rotor{
		char * RotoPhrase(const char * what, unsigned char count=ROTORMOVING);
		unsigned long _strlen_( const char * p);
		template <class T> void shuffle(void * arr, unsigned int index0, unsigned int index1);
	};
	namespace Numbers{
		char * convertNumberToPhrases(unsigned long long number=rand()%MAXNUMBERROTOR);
	};
};

};
