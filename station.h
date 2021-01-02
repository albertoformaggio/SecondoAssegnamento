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

	Platform getStandardPlatform();
	Platform getTransitPlatform();
	Train getParkedTrain();
	bool hasStandardPlatform();
	bool hasTransitPlatform();
	bool hasParkedTrain();
	void addParkedTrain(Train t);

	explicit Station(std::vector<Platform> tracks, int distance, std::string name, int number, std::priority_queue<Train> parked);
	~Station();
	//3 tipi standard, transit, parcheggio

private:
	const int kDistanceFromOrigin;
	const std::string st_name;
	const int trainNumber;
	std::priority_queue<Train> parked;
	std::vector<Platform> platforms;
};

#endif

