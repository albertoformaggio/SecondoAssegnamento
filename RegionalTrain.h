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
	RegionalTrain(int ID) : Train(ID) {}
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	void setSpeed(int s) override;
	Platform& requirePlatform(Station* st) override;
};

#endif