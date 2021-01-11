/* @author Michele Rieppi*/

#ifndef mainStation_h
#define mainStation_h

#include "station.h"

class mainStation : public Station {
public:
	mainStation(int distance, std::string name);
	Platform* getTransitPlatform(bool direction) override { throw std::exception(); }
};

#endif