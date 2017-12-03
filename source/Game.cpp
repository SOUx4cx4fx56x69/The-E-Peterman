#include "Game.hpp"
#include"Util.hpp"
namespace GameDrive{



const std::string NameKeys[CountGameKey]{
"Forward",
"Right",
"Down",
"Right",
"Action"
};

std::string GameKeys[CountGameKey] = {
"W", // Top
"A", // Left
"S", // Bottom
"D", // Right
"E" // Action
};

Drive::Drive(void){
	this->InitKeys();
}

void Drive::InitKeys(void){
	const char * Keys = Util::ReadFile(KEYSPATH);
	printf("%s\n",Keys);
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


}
