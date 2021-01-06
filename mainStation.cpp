/* @author Michele Rieppi */
#include "station.h"

mainStation::mainStation(int distance, std::string name)
	: Station(distance, name) 
{
		/*	Creo 4 binari standard per la stazione principale */
		standardPlatform bs1 = standardPlatform(false);
		addStandardPlatform(bs1);
		standardPlatform bs2 = standardPlatform(false);
		addStandardPlatform(bs2);
		standardPlatform bs3 = standardPlatform(false);
		addStandardPlatform(bs3);
		standardPlatform bs4 = standardPlatform(false);
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

standardPlatform Station::getStandardPlatform(){
	if (standardPlatforms.size() > 0)
		for (int i = 0; i < standardPlatforms.size(); i++) {
			if (standardPlatforms[i].isEmpty()) {
				return standardPlatforms[0];
				break;
			}
		}
}



