/*
	@author Anna Scarpa Falce
*/

#include "HSTrainSuper.h"

void HSTrainSuper::setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay)
{
	if (time leaving < 0)
		throw InvalidTime();
	if (time_arrival < time_leaving)
		time_arrival = (dis_st2 - dis_st1) / v_max + delay;
	speed = (dis_st2 - dis_st1) / (time_arrval - time_leaving - delay);
	if (speed > v_max)
		speed = v_max;
}
void HSTrainSuper::editDelay(int d)
{

}
Platform HSTrainSuper::requirePlatform(Station st)
{

}
void HSTrainSuper::leaving(Platform pl)
{

}
