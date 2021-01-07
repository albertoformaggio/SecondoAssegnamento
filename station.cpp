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

standardPlatform Station::getStandardPlatform() {
	if (standardPlatforms.size() > 0)
		for (int i = 0; i < standardPlatforms.size(); i++) {
			if (standardPlatforms[i].isEmpty()) {
				return standardPlatforms[i];
				break;
			}
		}
}