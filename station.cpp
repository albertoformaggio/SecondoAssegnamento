/*@author Michele Rieppi*/
#include "station.h"


Train* Station::getParkedTrain() {
	if (hasParkedTrain())
		throw std::exception();
	else return parked.front();
}

Train* Station::removeParkedTrain() {
	if (hasParkedTrain())
		throw std::exception();
	else {
		Train* rmv = parked.front();
		parked.pop();
		return rmv;
	}
}

Platform* Station::getStandardPlatform(bool direction) {
	if (standardPlatforms.size() > 0)
		for (int i = 0; i < standardPlatforms.size(); i++) {
			if (standardPlatforms[i].isEmpty() && standardPlatforms[i].startFromOrigin == direction) {
				return &standardPlatforms[i];
				break;
			}
		}
	return &parkPlatform(false, direction);
}

Station::~Station(){
	while (!parked.empty())
		parked.pop();
}

bool Station::operator<(const Event& other) const{
	return kDistanceFromOrigin < other.GetStation()->kDistanceFromOrigin;
}

