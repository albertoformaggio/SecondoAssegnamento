/* @author Michele Rieppi */
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	Platform* bs1 = new standardPlatform(false);
	addStandardPlatform(bs1);
	Platform* bs2 = new standardPlatform(false);
	addStandardPlatform(bs2);
	Platform* bs3 = new standardPlatform(false);
	addStandardPlatform(bs3);
	Platform* bs4 = new standardPlatform(false);
	addStandardPlatform(bs4);
	Platform* bt1 = new transitPlatform(false);
	addTransitPlatform(bt1);
	Platform* bt2 = new transitPlatform(false);
	addTransitPlatform(bt2);


}

Train* Station::getParkedTrain() {
	if (hasParkedTrain())
		throw std::exception();
	else return parked.front();
}

Train* Station::removeParkedTrain() {
	if (hasParkedTrain())
		throw std::exception();
	else {
		Train* rmv = parked.front();
		parked.pop();
		return rmv;
	}
}

transitPlatform localStation::getTransitPlatform(){
	return ;
}

standardPlatform localStation::getStandardPlatform(){
	return ;
}
