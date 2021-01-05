/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"
#include <cmath> 

void RegionalTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0);
{
	setAverageSpeed(from, to, time_leaving, time_arrival, dalay_time, v_max);
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
