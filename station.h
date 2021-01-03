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

	virtual Platform getStandardPlatform() = 0;
	Train getParkedTrain();
	bool hasStandardPlatform();
	bool hasTransitPlatform();
	bool hasParkedTrain();
	void addParkedTrain(Train t);

	~Station();

protected:

	void addTrack(Platform& track);

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name }, {};
	

private:

	std::priority_queue<Train*> parked;
	std::vector<Platform*> platforms;

};

class mainStation : public Station {

	mainStation(int distance, std::string name);
	Platform getStandardPlatform() override;
};

class localStation : public Station {

	localStation(int distance, std::string name);
	Platform getTransitPlatform();
	Platform getStandardPlatform() override;
};

#endif

