/* @author Michele Rieppi */

#ifndef station_h
#define station_h

#include "platform.h"
#include "train.h"
#include <iostream>
#include <vector>

class Station{
public:

	const int kDistanceFromOrigin;
	const std::string st_name;


	bool hasParkedTrain();
	Train& getParkedTrain();
	void addParkedTrain(Train& t);
	Train& removeParkedTrain();


	~Station();

protected:

	standardPlatform getStandardPlatform() = 0;
	void addStandardPlatform(Platform* track);

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}
	
	std::vector<Train*> parked;
	std::vector<Platform*> platforms;

};

class mainStation : public Station {

	mainStation(int distance, std::string name);

	standardPlatform getStandardPlatform() override;
};

class localStation : public Station {

	localStation(int distance, std::string name);
	
	void addTransitPlatform(Platform* track);
	transitPlatform* getTransitPlatform();
	standardPlatform getStandardPlatform() override;
};

#endif

