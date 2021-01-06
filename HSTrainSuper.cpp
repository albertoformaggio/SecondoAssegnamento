/*
	@author Anna Scarpa Falce
*/

#include "HSTrainSuper.h"
#include "platform.h"
#include "station.h"

void HSTrainSuper::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}
/*void HSTrainSuper::editDelay(int d)
{
	Train::editDelay(d);
}*/
Platform& HSTrainSuper::requirePlatform(Station& st)
{
	if (st.isLocal())
	{
		Platform& p = st.getTransitPlatform();
		p.reserve();
		return p;
	}
	else
	{
		Platform& p = st.getStandardPlatform();
		p.reserve();
		return p;
	}
}
/*void HSTrainSuper::leaving(Platform& pl)
{
	Train::leaving(pl);
}*/
