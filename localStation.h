/* @author Michele Rieppi*/

#ifndef localStation_h
#define localStation_h

#include "station.h"

class localStation : public Station {
public:
	localStation(int distance, std::string name);

	void addTransitPlatform(const transitPlatform track) { transitPlatforms.push_back(track); }

	Platform* getTransitPlatform(bool direction) override;
};

#endif