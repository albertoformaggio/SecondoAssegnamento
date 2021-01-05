/* @author Michele Rieppi */
#include <iostream>
#include <vector>
#include <queue>

#ifndef station_h
#define station_h

#include "platform.h"
#include "train.h"


class Station{
public:

	const int kDistanceFromOrigin;
	const std::string st_name;

	bool hasParkedTrain() { return parked.empty(); }
	Train* getParkedTrain();
	void addParkedTrain(Train& t) { parked.push(&t); }
	Train* removeParkedTrain();

	virtual standardPlatform getStandardPlatform() = 0;

	~Station();

protected:
	
	void addStandardPlatform(Platform* track) { standardPlatforms.push_back(&track); }

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}
	
	std::vector<transitPlatform> transitPlatforms;

private:
	std::queue<Train*> parked;
	std::vector<standardPlatform> standardPlatforms;
	

};

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);

	standardPlatform getStandardPlatform() override;
};

class localStation : public Station {
public:
	localStation(int distance, std::string name);
	
	void addTransitPlatform(Platform* track) { transitPlatforms.push_back(&track); } 

	transitPlatform getTransitPlatform();
	standardPlatform getStandardPlatform() override;
};

#endif

