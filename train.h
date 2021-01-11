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
	int speed = 0;
	int delay = 0;
protected:
	Train(int ID, bool d, int v) : identifying_number{ ID }, startFromOrigin{ d }, max_speed{ v }{}
public:
	const int max_speed;
	const bool startFromOrigin;
	const int identifying_number;
	inline int getSpeed() const { return speed; }
	inline int getDelay() const { return delay; }
	virtual void setSpeed(int s);
	inline void setDelay(int d) { delay = d; }
	virtual Platform* requirePlatform(Station* st) = 0;
	class InvalidTime {};
	class InvalidSpeed {};
	void editDelay(int d);
	void leaving(Platform& pl);
};


#endif