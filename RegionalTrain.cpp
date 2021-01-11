/*
	@author Anna Scarpa Falce
*/

#include "RegionalTrain.h"
#include "platform.h"
#include "station.h"

Platform* RegionalTrain::requirePlatform(Station* st)
{
	Platform* p = st->getStandardPlatform(startFromOrigin);
	p->reserve();
	return p;
}