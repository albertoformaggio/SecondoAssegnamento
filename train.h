#include "station.h"
#include "platform.h"

class Train
{
public:
	virtual void setSpeed() = 0;
	virtual void editDelay() = 0 ;
	virtual Platform requirePlatform(Station st) = 0;
	virtual void leaving(Platform p1) = 0;	//Quando parte semplicemente setta pl a libero 
};
