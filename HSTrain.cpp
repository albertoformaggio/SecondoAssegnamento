/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"

void HSTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}
/*void HSTrain::editDelay(int d)
{
	Train::editDelay(d);
}*/
Platform& HSTrain::requirePlatform(Station& st)
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
/*void HSTrain::leaving(Platform& pl)
{
	Train::leaving(pl);
}*/