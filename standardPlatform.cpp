/* @author Michele Rieppi */
#include "platform.h"

standardPlatform::standardPlatform(bool s) //Mancano controlli
	:Platform(occupied) {}

Platform::~Platform(){

}

int standardPlatform::fixSpeed(Train& t) const{
	return slowSpeed;
}