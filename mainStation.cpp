/* @author Michele Rieppi */
#include "station.h"

mainStation::mainStation(int distance, std::string name)
	: Station(distance, name) 
{
		/*	Creo 4 binari standard per la stazione principale */
		Platform* bs1 = new standardPlatform(false);
		addStandardPlatform(bs1);
		Platform* bs2 = new standardPlatform(false);
		addStandardPlatform(bs2);
		Platform* bs3 = new standardPlatform(false);
		addStandardPlatform(bs3);
		Platform* bs4 = new standardPlatform(false);
		addStandardPlatform(bs4);
		
}

Station::~Station(){

}

bool Station::hasParkedTrain(){
	return parked.size() > 0;
}

Train* Station::getParkedTrain(){
	if (hasParkedTrain())
		return parked.front();
	else throw std::exception();
}

void Station::addParkedTrain(Train& t){
	parked.push(&t);
}

Train* Station::removeParkedTrain(){
	if (hasParkedTrain())
		return parked.pop();
	else throw std::exception();
}

void mainStation::addStandardPlatform(Platform* track){
	standardPlatforms.push_back(&track);

}

standardPlatform* mainStation::getStandardPlatform(){
	return; //ritorna il primo elemento del vector di standardplatforms
}



