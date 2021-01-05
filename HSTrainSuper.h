/*
	@author Anna Scarpa Falce
*/
#include "train.h"

class HSTrainSuper : public train
{
private:

public:
	void setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay) override;
	void editDelay(int d) override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};

