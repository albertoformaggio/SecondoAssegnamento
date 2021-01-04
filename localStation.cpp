/* @author Michele Rieppi */
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	Platform* bs1 = new standardPlatform(0, 0);
	addStandardPlatform(bs1);
	Platform* bs2 = new standardPlatform(0, 0);
	addStandardPlatform(bs2);
	Platform* bs3 = new standardPlatform(0, 0);
	addStandardPlatform(bs3);
	Platform* bs4 = new standardPlatform(0, 0);
	addStandardPlatform(bs4);
	Platform* bt1 = new transitPlatform(1, 0);
	addTransitPlatform(bt1);
	Platform* bt2 = new transitPlatform(1, 0);
	addTransitPlatform(bt2);


}

transitPlatform* localStation::getTransitPlatform(){
	if (platforms[0] == nullptr)
		return platforms[0];
	else if (parked[1] == nullptr)
		return platforms[1];
}

transitPlatform localStation::getStandardPlatform(){
	return ;
}

Station::~Station() {

}

void Station::addStandardPlatform(Platform* track){
	platforms.push_back(&track);
}

void localStation::addTransitPlatform(Platform* track){
	platforms.push_back(&track)
}