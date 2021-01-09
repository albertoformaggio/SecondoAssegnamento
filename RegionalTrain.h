/*
	@author Anna Scarpa Falce
*/



#ifndef RegionalTrain_h
#define RegionalTrain_h

#include "train.h"

class RegionalTrain : public Train
{
public:
	const int v_max = 160;
	RegionalTrain(int ID, bool d) : Train(ID, d, v_max) {}
	Platform& requirePlatform(Station* st) override;
};

#endif