/* @author Michele Rieppi */
#ifndef STATION_H
#define STATION_H

#include "platform.h"
#include "train.h"
#include <queue>
#include <iostream>
#include <vector>


class Station
{
public:

	const int kDistanceFromOrigin;
	const std::string st_name;

	
	bool hasStandardPlatform(); //??
	bool hasTransitPlatform();	//??

	~Station();

protected:

	void addTrack(Platform& track);

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}
	
	std::vector<Train*> parked;
	std::vector<Platform*> platforms;

};

class mainStation : public Station {

	mainStation(int distance, std::string name);

	bool hasParkedTrain();
	Train getParkedTrain();
	void addParkedTrain(Train t);
	Train removeParkedTrain();
	standardPlatform getStandardPlatform();
};

class localStation : public Station {

	localStation(int distance, std::string name);
	transitPlatform getTransitPlatform();
	standardPlatform getStandardPlatform();
};

#endif

