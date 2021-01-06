/*
	@author Anna Scarpa Falce
*/

#include "train.h"

void Train::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time, int max_speed)
{
	if (time_leaving < 0)
		throw InvalidTime();
	int d = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin);
	if (time_arrival < time_leaving)
		time_arrival = (d / max_speed) + delay_time;

	setSpeed(d / (time_arrival - time_leaving - getDelay()));
	if (getSpeed() > max_speed)
		setSpeed(max_speed);
}
void Train::editDelay(int d)
{
	setDelay(getDelay() + d);
}
void Train::leaving(Platform& pl)
{
	pl.free();
}
