/*
	@author Anna Scarpa Falce
*/
#include "train.h"

#ifndef HSTrain_h
#define HSTrain_h

class HSTrain : public Train
{
private:

public:
	HSTrain(int ID) : Train(ID) {}
	void setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay) override;
	void editDelay(int d) override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};

#endif
