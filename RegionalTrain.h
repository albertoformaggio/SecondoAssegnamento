/*
	@author Anna Scarpa Falce
*/

#include "train.h"

#ifndef RegionalTrain_h
#define RegionalTrain_h

class RegionalTrain : public Train
{

public:
	const int v_max = 160;
	RegionalTrain(Station st, int ID) : Train(Station st, int ID);
	void setSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	void editDelay(int d) override;
	Platform& requirePlatform(Station& st) override;
	void leaving(Platform pl) override;
};

#endif