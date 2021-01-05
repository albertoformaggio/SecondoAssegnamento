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

bool Station::hasParkedTrain() {
	if (parked.size() > 0)
		return;
	throw std::exception();
}

Train* Station::getParkedTrain() {
	// TODO: inserire l'istruzione return qui
}

void Station::addParkedTrain(Train& t) {
	parked.push_back(&t);
}

Train* Station::removeParkedTrain() {
	if (this->hasParkedTrain() == true)
		return parked.pop_back();
}

void localStation::addTransitPlatform(Platform* track){

}

void localStation::addStandardPlatform(Platform* track){

}

transitPlatform* localStation::getTransitPlatform(){
	return nullptr;
}

standardPlatform* localStation::getStandardPlatform(){
	return nullptr;
}
