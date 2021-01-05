/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"

void HSTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	if (time leaving < 0)
		throw InvalidTime();
	if (time_arrival < time_leaving)
		time_arrival = (dis_st2 - dis_st1) / v_max + delay;
	speed = (dis_st2 - dis_st1) / (time_arrval - time_leaving - delay);
	if (speed > v_max)
		speed = v_max;
}
void HSTrain::editDelay(int d)
{

}
Platform& HSTrain::requirePlatform(Station& st)
{

}
void HSTrain::leaving(Platform& pl)
{

}