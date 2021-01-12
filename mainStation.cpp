/* @author Michele Rieppi */

#include "station.h"
#include "mainStation.h"
#include "standardPlatform.h"


//Costruttore main station
mainStation::mainStation(int distance, std::string name)
	: Station(distance, name) 
{
		/*	Creo 4 binari standard per la stazione principale */
		standardPlatform bs1 = standardPlatform(false,true);
		addStandardPlatform(bs1);
		standardPlatform bs2 = standardPlatform(false,false);
		addStandardPlatform(bs2);
		standardPlatform bs3 = standardPlatform(false,true);
		addStandardPlatform(bs3);
		standardPlatform bs4 = standardPlatform(false,false);
		addStandardPlatform(bs4);
		
}




