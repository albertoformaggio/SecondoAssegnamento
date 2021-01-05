/* @author Michele Rieppi */
#include "platform.h"

transitPlatform::transitPlatform(bool s) //Mancano controlli
	:Platform(occupied) {}

Platform::~Platform(){

}

int transitPlatform::fixSpeed(Train& t) const {
	return t.getSpeed();
}