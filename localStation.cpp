/* @author Michele Rieppi */
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	standardPlatform bs1 = standardPlatform(false);
	addStandardPlatform(bs1);
	standardPlatform bs2 = standardPlatform(false);
	addStandardPlatform(bs2);
	standardPlatform bs3 = standardPlatform(false);
	addStandardPlatform(bs3);
	standardPlatform bs4 = standardPlatform(false);
	addStandardPlatform(bs4);
	transitPlatform bt1 = transitPlatform(false);
	addTransitPlatform(bt1);
	transitPlatform bt2 = transitPlatform(false);
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
