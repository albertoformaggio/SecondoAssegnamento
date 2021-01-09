/*
	@author Anna Scarpa Falce
*/

#include "HSTrain.h"
#include "platform.h"
#include "station.h"
#include "localStation.h"
#include "mainStation.h"

Platform& HSTrain::requirePlatform(Station* st)
{
	localStation* ls = dynamic_cast<localStation*>(st);
	if (ls != nullptr)
	{
		Platform& p = ls->getTransitPlatform(startFromOrigin);
		p.reserve();
		return p;
	}
	else
	{
		Platform& p = st->getStandardPlatform(startFromOrigin);
		p.reserve();
		return p;
	}
}
