/*
	@author Anna Scarpa Falce
*/

#include "HSTrainSuper.h"
#include "localStation.h"
#include "mainStation.h"
#include "platform.h"
#include "station.h"

Platform* HSTrainSuper::requirePlatform(Station* st)
{
	localStation* ls = dynamic_cast<localStation*>(st);
	if (ls != nullptr)
	{
		Platform* p = st->getTransitPlatform(startFromOrigin);
		p->reserve();
		return p;
	}
	else
	{
		Platform* p = st->getStandardPlatform(startFromOrigin);
		p->reserve();
		return p;
	}
	
}
