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
	if (parked.size() > 0)
		return ;
	throw std::exception();
}

Train& Station::getParkedTrain(){
	// TODO: inserire l'istruzione return qui
}

void Station::addParkedTrain(Train& t){
	parked.push_back(&t);
}

Train& Station::removeParkedTrain(){
	if (this->hasParkedTrain() == true)
		return parked.pop_back();
}

void mainStation::addStandardPlatform(Platform* track){
	standardPlatforms.push_back(&track);

}

standardPlatform* mainStation::getStandardPlatform(){
	return nullptr;
}



