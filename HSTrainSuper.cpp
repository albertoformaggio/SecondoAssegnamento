/*
	@author Anna Scarpa Falce
*/

#include "HSTrainSuper.h"

void HSTrainSuper::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	if (time_leaving < 0)
		throw InvalidTime();
	int d = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin);
	if (time_arrival < time_leaving)
		time_arrival = (d / v_max) + delay_time;

	setSpeed(d / (time_arrival - time_leaving - getDelay()));
	if (getSpeed() > v_max)
		setSpeed(v_max);
}
void HSTrainSuper::editDelay(int d)
{

}
Platform& HSTrainSuper::requirePlatform(Station& st)
{

}
void HSTrainSuper::leaving(Platform& pl)
{

}
