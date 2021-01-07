/* @author Michele Rieppi */
#include "platform.h"

standardPlatform::standardPlatform(bool s) //Mancano controlli
	:Platform(occupied) {}

int standardPlatform::fixSpeed(const Train& t) const {
	return slowSpeed;
}