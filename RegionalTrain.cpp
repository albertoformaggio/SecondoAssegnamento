/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"

void RegionalTrain::setSpeed()
{
	
}
void RegionalTrain::editDelay()
{

}
Platform RegionalTrain::requirePlatform(Station st)
{
	if (st.hasParkedTrain())
		return addParkedTrain(); 
	if (!st.hasStandardPlatform())
		return addParkedTrain();
	else
		st.getStandardPlatform();
}
void RegionalTrain::leaving(Platform pl)
{
	int time = ;
	event e(4, time, *this, pl);
	addEvent(e);
}
