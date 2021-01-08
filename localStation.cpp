/* @author Michele Rieppi */

#include "localStation.h"
#include "transitPlatform.h"
#include "standardPlatform.h"
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	standardPlatform bs1 = standardPlatform(false,true);
	addStandardPlatform(bs1);
	standardPlatform bs2 = standardPlatform(false,true);
	addStandardPlatform(bs2);
	standardPlatform bs3 = standardPlatform(false,false);
	addStandardPlatform(bs3);
	standardPlatform bs4 = standardPlatform(false,false);
	addStandardPlatform(bs4);
	transitPlatform bt1 = transitPlatform(false,true);
	addTransitPlatform(bt1);
	transitPlatform bt2 = transitPlatform(false,false);
	addTransitPlatform(bt2);


}

transitPlatform localStation::getTransitPlatform(bool direction){
	if(transitPlatforms.size() > 0)
		for (int i = 0; i < transitPlatforms.size(); i++) {
			if (transitPlatforms[i].isEmpty() && transitPlatforms[i].startFromOrigin == direction) {
				return transitPlatforms[i];
				break;
			}
		}
}


