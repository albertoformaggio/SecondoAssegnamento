/* @author Michele Rieppi */
#include "standardPlatform.h"

//Costruttore binario standard
standardPlatform::standardPlatform(bool s, bool d)
	:Platform(occupied, startFromOrigin) {}

//Ritorna la velocità a cui deve andare il treno nel tratto lento
int standardPlatform::fixSpeed(const Train& t) const {
	return slowSpeed;
}