/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"

void HSTrain::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}
void HSTrain::editDelay(int d)
{
	Train::editDelay(d);
}
Platform& HSTrain::requirePlatform(Station& st)
{

}
void HSTrain::leaving(Platform& pl)
{

}