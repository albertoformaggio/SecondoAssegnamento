/* @author Michele Rieppi */
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#ifndef station_h
#define station_h

class Train;
#include "transitPlatform.h"

class Station {
public:

	const int kDistanceFromOrigin;
	const std::string st_name;

	virtual bool hasParkedTrain() { return parked.empty(); }
	Train* getParkedTrain();
	void addParkedTrain(Train& t) { parked.push(&t); }
	Train* removeParkedTrain();

	standardPlatform getStandardPlatform(bool direction);
	virtual transitPlatform getTransitPlatform(bool direction) = 0;
	~Station();

protected:

	void addStandardPlatform(const standardPlatform track) { standardPlatforms.push_back(track); }

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}

	std::vector<transitPlatform> transitPlatforms;
	std::vector<standardPlatform> standardPlatforms;

private:

	std::queue<Train*> parked;

};

#endif

