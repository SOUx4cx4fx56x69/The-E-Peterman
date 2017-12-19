#pragma once
#include<string>
#define KEYSPATH "Settings/Keys.bnd"
#define MOVINGGAME 2

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
void InitKeys(void);
protected:
public:
void StartGame(void);
Drive(void);

};

};
