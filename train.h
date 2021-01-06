/*
	@author Anna Scarpa Falce
*/
#include <cmath>

#ifndef train_h
#define train_h

class Station;
class Platform;

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
	inline void setSpeed(int s) { speed = s; }
	inline void setDelay(int d) { delay = d; }
	virtual void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time = 0) = 0;
	virtual Platform& requirePlatform(Station& st) = 0;
	class InvalidTime {};
	void setAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, int delay_time, int max_speed);
	void editDelay(int d);
	void leaving(Platform& pl);
};


#endif