/*
	@author Anna Scarpa Falce
*/

#ifndef train_h
#define train_h

#include "station.h"
#include "platform.h"

class Train
{
private:
	int speed;
	int delay = 0;
protected:
	Train(int ID) : identifying_number{ ID } {}
	
public:
	const int identifying_number;
	const int distanceFromPark = 5;
	const int speedInStation = 80;
	inline int getSpeed() const { return speed; }
	inline int getDelay() const { return delay; }
	inline int setSpeed(int s) { speed = s; }
	inline int setDelay(int d) { delay = d; }
	virtual void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) = 0;
	virtual Platform& requirePlatform(Station& st) = 0;
	class InvalidTime {};
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time, int max_speed);
	void editDelay(int d);
	void leaving(Platform& pl);
};

#endif