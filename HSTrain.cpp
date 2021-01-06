/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"
#include "platform.h"
#include "station.h"

void HSTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}

void HSTrain::setSpeed(int s)
{
	Train::setSpeed(s);     //da controllare se chiama da sola quella base o no
	if (s > v_max)
		Train::setSpeed(v_max);
}

Platform& HSTrain::requirePlatform(Station& st)
{
	
	/*if (st.isLocal())
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
	}*/
	return st.getStandardPlatform();
}
