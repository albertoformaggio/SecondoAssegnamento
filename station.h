/* @author Michele Rieppi */
#include <iostream>
#include <vector>

#ifndef station_h
#define station_h

#include "platform.h"
#include "train.h"


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

	virtual standardPlatform getStandardPlatform() = 0;
	void addStandardPlatform(Platform* track) = 0;

	explicit Station(int distance, std::string name)
		: kDistanceFromOrigin{ distance }, st_name{ name } {}
	

	std::vector<Train*> parked;
	std::vector<standardPlatform*> standardPlatforms;
	std::vecotr<transitPlatform*> transitPlatforms;

};

class mainStation : public Station {

	mainStation(int distance, std::string name);

	void addStandardPlatform(Platform* track) override;

	standardPlatform* getStandardPlatform() override;
};

class localStation : public Station {

	localStation(int distance, std::string name);
	
	void addTransitPlatform(Platform* track);

	void addStandardPlatform(Platform* track) override;

	transitPlatform* getTransitPlatform();
	standardPlatform* getStandardPlatform() override;
};

#endif

