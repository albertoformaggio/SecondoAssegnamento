/* @author Michele Rieppi */
#include "platform.h"

Platform::Platform(bool t, bool s) : type { t }, status{ s } {}

bool Platform::isEmpty(){
	return status == 0;
}

void Platform::free(){
	status = 0;
}

void Platform::reserve() {
	status = 1;
}
