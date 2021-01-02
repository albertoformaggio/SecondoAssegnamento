/* @author Michele Rieppi */
#include "station.h"

Station::Station(std::vector<Platform> tracks, int distance, std::string name, int number, std::vector<Train> park)
	: kDistanceFromOrigin{ distance }, st_name{ name }, trainNumber{ number }, parked{ park }
{
	/*	Creo 6 binari standard per la stazione secondaria */
	Platform bs1 = Platform(0, 0);
	tracks.push_back(bs1);
	Platform bs2 = Platform(0, 0);
	tracks.push_back(bs2);
	Platform bs3 = Platform(0, 0);
	tracks.push_back(bs3);
	Platform bs4 = Platform(0, 0);
	tracks.push_back(bs4);
	Platform bt1 = Platform(1, 0);
	tracks.push_back(bt1);
	Platform bt2 = Platform(1, 0);
	tracks.push_back(bt2);


}

Station::~Station() {

}