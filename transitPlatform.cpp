/* @author Michele Rieppi */
#include "platform.h"

transitPlatform::transitPlatform(bool s, bool d) //Mancano controlli
	:Platform(occupied, startFromOrigin) {}

Platform::~Platform(){

}

int transitPlatform::fixSpeed(const Train& t) const {
	return t.getSpeed();
}