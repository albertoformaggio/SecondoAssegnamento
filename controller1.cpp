/*
	@author Anna Scarpa Falce
*/

#include "controller.h"
#include "station.h"

int Controller::getAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, Train* t, int delay_time)
{
	const int minPerHours = 60;

	if (time_leaving < 0 || delay_time < 0)
		return -1;

	int timeAtFixedSpeed = (2 * t->distanceFromPark / t->speedInStation) * minPerHours;
	int distance = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin) - 2 * t->distanceFromPark; //funzione per avere dist da parcheggio(5);
	int minimumTime = (int)(distance / t->max_speed) * minPerHours + timeAtFixedSpeed + delay_time + t->getDelay();
	
	if (time_arrival - time_leaving < minimumTime)
		time_arrival = minimumTime;

	int deltaT = time_arrival - time_leaving;
	int time = deltaT - t->getDelay() - timeAtFixedSpeed;
	int v = (int)(distance / time);
	return v;
}