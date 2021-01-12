/*@author Michele Rieppi*/
#include "station.h"

//Ritorna il treno più vecchio parcheggiato
Train* Station::getParkedTrain() {
	if (!hasParkedTrain())
		throw std::exception();
	else return parked.front();
}

//Rimuove il treno più vecchio parcheggiato e lo ritorna
Train* Station::removeParkedTrain() {
	if (!hasParkedTrain())
		throw std::exception();
	else {
		Train* rmv = parked.front();
		parked.pop();
		return rmv;
	}
}

//Ritorna una binario standard
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

//Distruttore di station
Station::~Station(){
	while (!parked.empty())
		parked.pop();
}


bool isFartherThan(const Station* first, const Station* other){

	return first->kDistanceFromOrigin < other->kDistanceFromOrigin;
}


