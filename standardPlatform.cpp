/* @author Michele Rieppi */
#include "standardPlatform.h"

standardPlatform::standardPlatform(bool s, bool d) //Mancano controlli
	:Platform(occupied, startFromOrigin) {}

int standardPlatform::fixSpeed(const Train& t) const {
	return slowSpeed;
}