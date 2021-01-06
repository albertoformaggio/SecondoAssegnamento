/*
	@author Anna Scarpa Falce
*/

#include "HSTrainSuper.h"

void HSTrainSuper::setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0)
{
	Train::setAverageSpeed(from, to, time_leaving, time_arrival, delay_time, v_max);
}
/*void HSTrainSuper::editDelay(int d)
{
	Train::editDelay(d);
}*/
Platform& HSTrainSuper::requirePlatform(Station& st)
{

}
/*void HSTrainSuper::leaving(Platform& pl)
{
	Train::leaving(pl);
}*/
