/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"

void RegionalTrain::setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay)
{
	if (time leaving < 0)
		throw InvalidTime();
	if (time_arrival < time_leaving)
		time_arrival = (dis_st2 - dis_st1) / v_max + delay;
	speed = (dis_st2 - dis_st1) / (time_arrval - time_leaving - delay);
	if (speed > v_max)
		speed = v_max;
}

void RegionalTrain::editDelay(int d)
{

}
Platform RegionalTrain::requirePlatform(Station st)
{
	if (st.hasParkedTrain())
		return addParkedTrain(); 
	if (!st.hasStandardPlatform())
		return addParkedTrain();
	else
		st.getStandardPlatform();
}
void RegionalTrain::leaving(Platform pl)
{
	int time = ;
	event e(4, time, *this, pl);
	addEvent(e);
}
