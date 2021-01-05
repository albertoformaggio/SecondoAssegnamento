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
	const int v_max = 240;
	HSTrain(int ID) : Train(ID) {}
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	void editDelay(int d) override;
	Platform& requirePlatform(Station& st) override;
	void leaving(Platform& pl) override;
};

#endif
