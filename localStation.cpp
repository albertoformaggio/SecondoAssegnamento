/* @author Michele Rieppi */
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	Platform* bs1 = new standardPlatform(0, 0);
	addTrack(&bs1);
	Platform* bs2 = new standardPlatform(0, 0);
	addTrack(&bs2);
	Platform* bs3 = new standardPlatform(0, 0);
	addTrack(&bs3);
	Platform* bs4 = new standardPlatform(0, 0);
	addTrack(&bs4);
	Platform* bt1 = new transitPlatform(1, 0);
	addTrack(&bt1);
	Platform* bt2 = new transitPlatform(1, 0);
	addTrack(&bt2);


}

Platform localStation::getTransitPlatform(){
	if (bt1.isEmpty() == 0)
		return bt1;
	else if (bt2.isEmpty() == 0)
		return bt2;
}

transitPlatform localStation::getStandardPlatform(){
	return ;
}

Station::~Station() {

}

void Station::addTrack(Platform& track) {
	parked.push_back(track);
}