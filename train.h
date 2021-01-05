/*
	@author Anna Scarpa Falce
*/

#include "station.h"
#include "platform.h"
#include "event.h"

class train
{
public:
	virtual void setSpeed(int dis_st1, int dis_st2, int time_leaving, int time_arrival, int delay) = 0;
	virtual void editDelay(int d) = 0 ;
	virtual Platform requirePlatform(Station st) = 0;
	virtual void leaving(Platform p1) = 0;	//Quando parte semplicemente setta pl a libero 
	class InvalidTime {};
};
