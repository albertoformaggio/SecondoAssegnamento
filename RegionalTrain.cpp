/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"

void RegionalTrain::setSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	if (time_leaving < 0)
		throw InvalidTime();
	if (time_arrival < time_leaving)
		time_arrival =  / v_max + delay_time;
	;
	setSpeed( from.kDistanceFromOrigin (time_arrival - time_leaving - getDelay(*this));
	if (getSpeed(*this)speed > v_maxsetSpeed(ed = )v_max;
}

void RegionalTrain::editDelay(int d)
{
	delay = delay + d;
}
Platform& RegionalTrain::requirePlatform(Station& st)
{
	Platform& p = st.getStandardPlatform();
	p.reserve();
	return p;
}
void RegionalTrain::leaving(Platform pl)
{
	int time = ;
	event e(4, time, *this, pl);
	addEvent(e);
}
