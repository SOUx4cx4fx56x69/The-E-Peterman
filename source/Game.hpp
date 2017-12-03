#pragma once
#include<string>
#define KEYSPATH "Settings/Keys.bnd"

namespace GameDrive{
const unsigned char CountGameKey = 5;
extern std::string GameKeys[CountGameKey];
extern const std::string NameKeys[CountGameKey];


class Drive{
private:
void InitKeys(void);
protected:
public:
void StartGame(void);
Drive(void);

};

};
