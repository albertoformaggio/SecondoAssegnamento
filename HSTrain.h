/*
	@author Anna Scarpa Falce
*/

#ifndef HSTrain_h
#define HSTrain_h

#include "train.h"

class HSTrain : public Train
{
private:

public:
	//const int v_max = 240;
	HSTrain(int ID, bool d) : Train(ID, d, 240) {}
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	Platform& requirePlatform(Station* st) override;
	void setSpeed(int s) override;
};

#endif
