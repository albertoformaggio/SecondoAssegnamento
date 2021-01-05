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

Train* Station::getParkedTrain(){
	if (hasParkedTrain())
		throw std::exception();
	else return parked.front();
}

Train* Station::removeParkedTrain(){
	if (hasParkedTrain())
		throw std::exception();
	else {
		Train* rmv = parked.front();
		parked.pop();
		return rmv;
	}
}

standardPlatform mainStation::getStandardPlatform(){
	return; //Ritorna il primo elemento disponibile del vettore dei binari
}



