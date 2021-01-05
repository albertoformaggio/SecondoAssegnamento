/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"
#include <cmath>

void RegionalTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	if (time_leaving < 0)
		throw InvalidTime();
	int d = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin);
	if (time_arrival < time_leaving)
		time_arrival = (d / v_max) + delay_time;
	
	setSpeed(d/(time_arrival - time_leaving - getDelay()));
	if (getSpeed() > v_max)
		setSpeed(v_max);
}

void RegionalTrain::editDelay(int d)
{
	setDelay(getDelay() +d);
}
Platform& RegionalTrain::requirePlatform(Station& st)
{
	Platform& p = st.getStandardPlatform();
	p.reserve();
	return p;
}
void RegionalTrain::leaving(Platform& pl)
{
	pl.free();
}
