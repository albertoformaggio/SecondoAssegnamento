/*
	@author Anna Scarpa Falce
*/

#include "train.h"

class RegionalTrain : public train
{
private:
	const int v_max = 160;
	int speed;
	int delay;
	const Station origin;
	const int identifying_number;
public:
	RegionalTrain(Station st, int ID);
	void setSpeed(int dis_st1, int dis_st2, int time_leaving, int& time_arrival, int delay) override;
	void editDelay(int d) override;
	Platform requirePlatform(Station st) override;
	void leaving(Platform pl) override;
};
