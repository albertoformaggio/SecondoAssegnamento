/*
	@author Anna Scarpa Falce
*/
#include "train.h"

#ifndef HSTrainSuper_h
#define HSTrainSuper_h
class HSTrainSuper : public Train
{
private:

public:
	HSTrainSuper(int ID) : Train(ID) {}
	void setSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) override;
	void editDelay(int d) override;
	Platform& requirePlatform(Station& st) override;
	void leaving(Platform pl) override;
};

#endif