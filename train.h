/*
	@author Anna Scarpa Falce
*/

#include "station.h"
#include "platform.h"
#include "event.h"

#ifndef train_h
#define train_h

class Train
{
private:
	int speed;
	int delay = 0;
protected:
	Train(int ID) : identifying_number{ ID } {}
	
public:
	const int identifying_number;
	inline int getSpeed() const { return speed; }
	inline int getDelay() const { return delay; }
	inline int setSpeed(int s) { speed = s; }
	inline int setDelay(int d) { delay = d; }
	virtual void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) = 0;
	virtual void editDelay(int d) = 0 ;
	virtual Platform& requirePlatform(Station& st) = 0;
	virtual void leaving(Platform& pl) = 0;	//Quando parte semplicemente setta pl a libero 
	class InvalidTime {};
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time, int max_speed)
	{
		if (time_leaving < 0)
			throw InvalidTime();
		int d = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin);
		if (time_arrival < time_leaving)
			time_arrival = (d / max_speed) + delay_time;

		setSpeed(d / (time_arrival - time_leaving - getDelay()));
		if (getSpeed() > max_speed)
			setSpeed(max_speed);
	}
};

#endif