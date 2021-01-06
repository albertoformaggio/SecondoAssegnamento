/*
	@author Anna Scarpa Falce
*/


#ifndef HSTrainSuper_h
#define HSTrainSuper_h

#include "train.h"
class HSTrainSuper : public Train
{
private:

public:
	const int v_max = 300;
	HSTrainSuper(int ID) : Train(ID) {}
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	//void editDelay(int d);
	Platform& requirePlatform(Station& st) override;
	//void leaving(Platform& pl) override;
};

#endif