/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"
#include "platform.h"
#include "station.h"
#include <cmath> 

void RegionalTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}

void RegionalTrain::setSpeed(int s)
{
	Train::setSpeed(s);     //da controllare se chiama da sola quella base o no
	if (s > v_max)
		Train::setSpeed(v_max);
}

Platform& RegionalTrain::requirePlatform(Station& st)
{
	Platform& p = st.getStandardPlatform();
	p.reserve();
	return p;
}