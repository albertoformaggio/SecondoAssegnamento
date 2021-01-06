/* @author Michele Rieppi */
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#include "platform.h"
#include "train.h"

#ifndef station_h
#define station_h

class Station {
public:

	const int kDistanceFromOrigin;
	const std::string st_name;

	bool hasParkedTrain() { return parked.empty(); }
	Train* getParkedTrain();
	void addParkedTrain(Train& t) { parked.push(&t); }
	Train* removeParkedTrain();

	standardPlatform getStandardPlatform();

	~Station();

protected:

	void addStandardPlatform(standardPlatform track) { standardPlatforms.push_back(track); }

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}

	std::vector<transitPlatform> transitPlatforms;
	std::vector<standardPlatform> standardPlatforms;

private:

	std::queue<Train*> parked;

};

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);

};

class localStation : public Station {
public:
	localStation(int distance, std::string name);

	void addTransitPlatform(transitPlatform track) { transitPlatforms.push_back(track); }

	transitPlatform getTransitPlatform();
};

#endif

