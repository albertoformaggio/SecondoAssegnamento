/* @author Michele Rieppi */
#include "platform.h"

standardPlatform::standardPlatform(bool t, bool s) //Mancano controlli
	:Platform(type, status) {}

Platform::~Platform(){

}

bool Platform::isEmpty() {
	return status == 0;
}

void Platform::free() {
	status = 0;
}

void Platform::reserve() {
	status = 1;
}

void standardPlatform::fixSpeed(Train t) {
	t.setSpeed();
}
