/*!
	@author Formaggio Alberto
*/
#include "train.h"
#include "station.h"

#ifndef Event_h
#define Event_h

class Event
{
public:
	Event(int time, Train& train, Station& st);
	int GetTime() const { return time_; }
	Train* GetTrain() const { return train_; }
	Station* GetStation() const { return station_; }
	virtual void performAction() = 0;

private:
	int time_;
	Train* train_;		//forse unique_ptr ?
	Station* station_;
};

class PlatformRequest : public Event
{
	void performAction() override;
};

class StationAnswer : public Event
{
	void performAction() override;
};

class TrainStop : public Event
{
	void performAction() override;
};

class TrainDeparture : public Event
{
	void performAction() override;
};

#endif // !Event