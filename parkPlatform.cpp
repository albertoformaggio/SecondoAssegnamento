/* @author Michele Rieppi */
#include "parkPlatform.h"

parkPlatform::parkPlatform(bool s, bool d)
	:Platform(occupied, startFromOrigin) {}

int parkPlatform::fixSpeed(const Train& t) const
{
	return 0;
}
