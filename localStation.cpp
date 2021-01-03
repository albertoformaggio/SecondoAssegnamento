/* @author Michele Rieppi */
#include "station.h"

localStation::localStation(int distance, std::string name)
	: Station(distance, name)
{
	/*	Creo 6 binari standard per la stazione secondaria */
	Platform* bs1 = new standardPlatform(0, 0);
	//tracks.push_back(bs1);
	Platform* bs2 = new standardPlatform(0, 0);
	//tracks.push_back(bs2);
	Platform* bs3 = new standardPlatform(0, 0);
	//tracks.push_back(bs3);
	Platform* bs4 = new standardPlatform(0, 0);
	//tracks.push_back(bs4);
	Platform* bt1 = new transitPlatform(1, 0);
	//tracks.push_back(bt1);
	Platform* bt2 = new transitPlatform(1, 0);
	//tracks.push_back(bt2);


}

Station::~Station() {

}