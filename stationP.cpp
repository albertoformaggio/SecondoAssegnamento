/* @author Michele Rieppi */
#include "station.h"

Station::Station(std::vector<Platform> tracks, int distance, std::string name, int number, std::vector<Train> park)
	: kDistanceFromOrigin{ distance }, st_name{ name }, trainNumber{ number }, parked{ park }
{
		/*	Creo 4 binari standard per la stazione principale */
		Platform bs1 = Platform(0, 0);
		tracks.push_back(bs1);
		Platform bs2 = Platform(0, 0);
		tracks.push_back(bs2);
		Platform bs3 = Platform(0, 0);
		tracks.push_back(bs3);
		Platform bs4 = Platform(0, 0);
		tracks.push_back(bs4);
		
}

Station::~Station(){

}

void Station::addParkedTrain(Train t) {
	parked.push_back(t);
}



