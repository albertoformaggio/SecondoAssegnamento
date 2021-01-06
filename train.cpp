/*
	@author Anna Scarpa Falce
*/

#include "train.h"

void Train::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time, int max_speed)
{
	if (time_leaving < 0)
		throw InvalidTime();
	int distance = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin)-2*distanceFromPark; //funzione per avere dist da parcheggio(5);
	if (time_arrival < time_leaving)
		time_arrival = (distance / max_speed) + delay_time;
	int time = (time_arrival - time_leaving - getDelay() - 2*distanceFromPark / speedInStation);
	setSpeed(distance / time );
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
