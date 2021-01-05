/* @author Michele Rieppi */
#include "platform.h"

transitPlatform::transitPlatform(bool t, bool s) //Mancano controlli
	:Platform(type, status) {}

bool Platform::isEmpty(){
	return status == 0;
}

Platform::~Platform(){

}

void Platform::free(){
	status = 0;
}

void Platform::reserve() {
	status = 1;
}
