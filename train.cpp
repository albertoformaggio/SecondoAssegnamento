/*
	@author Anna Scarpa Falce
*/

#include "train.h"
#include "station.h"
#include "platform.h"

void Train::setSpeed(int s)
{ 
	if (s < 0)
		throw InvalidSpeed();
	if(s > max_speed)
		speed = max_speed;
	//else
		speed = s;	
}

void Train::editDelay(int d)
{
	setDelay(getDelay() + d);
}
void Train::leaving(Platform& pl)
{
	pl.free();
}
