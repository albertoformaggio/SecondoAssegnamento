/* @author Michele Rieppi */
#include "station.h"

mainStation::mainStation(int distance, std::string name)
	: Station(distance, name) 
{
		/*	Creo 4 binari standard per la stazione principale */
		Platform* bs1 = new standardPlatform(0, 0);
		addStandardPlatform(bs1);
		Platform* bs2 = new standardPlatform(0, 0);
		addStandardPlatform(bs2);
		Platform* bs3 = new standardPlatform(0, 0);
		addStandardPlatform(bs3);
		Platform* bs4 = new standardPlatform(0, 0);
		addStandardPlatform(bs4);
		
}

Station::~Station(){

}

bool Station::hasParkedTrain(){
	return parked.size() > 0;
}

Train Station::getParkedTrain() {
	return ;
}

void Station::addParkedTrain(Train t) {
	parked.push_back(&t);
}

Train Station::removeParkedTrain() {
	if(this->hasParkedTrain() == true)
		return ;
}

standardPlatform mainStation::getStandardPlatform(){
	return ;
}

void Station::addStandardPlatform(Platform* track) {
	platforms.push_back(&track);
}






