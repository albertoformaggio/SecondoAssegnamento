/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"

void HSTrain::setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay)
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
Platform HSTrain::requirePlatform(Station st)
{

}
void HSTrain::leaving(Platform pl)
{

}