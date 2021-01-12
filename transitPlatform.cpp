/* @author Michele Rieppi */
#include "transitPlatform.h"

//Costruttore binario di transito
transitPlatform::transitPlatform(bool s, bool d) 
	:Platform(occupied, startFromOrigin) {}

Platform::~Platform(){

}

//Ritorna la velocit� del treno
int transitPlatform::fixSpeed(const Train& t) const {
	return t.getSpeed();
}