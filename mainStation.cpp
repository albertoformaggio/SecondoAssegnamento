#include "station.h"
#include "station.h"
/* @author Michele Rieppi */
#include "station.h"

mainStation::mainStation(int distance, std::string name)
	: Station(distance, name) 
{
		/*	Creo 4 binari standard per la stazione principale */
		Platform* bs1 = new standardPlatform(0, 0);
		addTrack(&bs1);
		Platform* bs2 = new standardPlatform(0, 0);
		addTrack(&bs2);
		Platform* bs3 = new standardPlatform(0, 0);
		addTrack(&bs3);
		Platform* bs4 = new standardPlatform(0, 0);
		addTrack(&bs4);
		
}

Station::~Station(){

}

bool mainStation::hasParkedTrain(){
	if (parked.size() > 0)
		return true;
	return false;
}

Train mainStation::getParkedTrain(){
	return ;
}

void mainStation::addParkedTrain(Train t) {
	parked.push_back(&t);
}

Train mainStation::removeParkedTrain() {
	return parked.pop_back();
}

standardPlatform mainStation::getStandardPlatform(){
	return ;
}

void Station::addTrack(Platform& track){
	parked.push_back(track);
}








