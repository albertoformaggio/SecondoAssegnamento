/* @author Michele Rieppi */
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#ifndef station_h
#define station_h

class Train;
#include "platform.h"

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

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);
	transitPlatform getTransitPlatform(bool direction) override { throw std::exception(); }
};

class localStation : public Station {
public:
	localStation(int distance, std::string name);

	void addTransitPlatform(const transitPlatform track) { transitPlatforms.push_back(track); }

	transitPlatform getTransitPlatform(bool direction) override;
};

#endif

