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

	bool hasParkedTrain();
	Train* getParkedTrain();
	void addParkedTrain(Train& t);
	Train* removeParkedTrain();
	virtual standardPlatform getStandardPlatform() = 0;

	~Station();

protected:
	
	virtual void addStandardPlatform(Platform* track) = 0;

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}
	
private:
	std::queue<Train*> parked;
	std::vector<standardPlatform> standardPlatforms;
	std::vector<transitPlatform> transitPlatforms;

};

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);

	standardPlatform getStandardPlatform() override;

protected:
	void addStandardPlatform(Platform* track) override;
};

class localStation : public Station {
public:
	localStation(int distance, std::string name);
	
	void addTransitPlatform(Platform* track);

	transitPlatform getTransitPlatform();
	standardPlatform getStandardPlatform() override;

protected:
	void addStandardPlatform(Platform* track) override;
};

#endif

