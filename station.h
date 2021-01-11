/* @author Michele Rieppi */
#include <iostream>
#include <vector>
#include <queue>
#include <string>

#ifndef station_h
#define station_h

class Train;
class Platform;

#include "transitPlatform.h"
#include "standardPlatform.h"
#include "parkPlatform.h"
#include "event.h"

class Station {
public:

	const int kDistanceFromOrigin;
	const std::string st_name;

	virtual bool hasParkedTrain() { return parked.empty(); }
	Train* getParkedTrain();
	void addParkedTrain(Train& t) { parked.push(&t); }
	Train* removeParkedTrain();

	Platform* getStandardPlatform(bool direction);
	virtual transitPlatform getTransitPlatform(bool direction) = 0;
	~Station();

	bool operator< (const Event& other) const;

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

