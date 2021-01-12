/* @author Michele Rieppi */
#include "parkPlatform.h"

//Costruttore binario parcheggio
parkPlatform::parkPlatform(bool s, bool d)
	:Platform(occupied, startFromOrigin) {}

int parkPlatform::fixSpeed(const Train& t) const
{
	return 0;
}
