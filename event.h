#include "train.h"
#include "station.h"

#ifndef Event_h
#define Event_h
class Event
{
	Event(EventType e_type, Time time, Train train, Station st);
	Time GetTime() const;
	Train GetTrain() const;
	EventType GetType() const;
	Station GetStation() const;

private:
	EventType type_;
	Time time_;
	Train train_;
	Station station_;
};

enum class EventType
{
	kTrainRequest,
	kStationAnswer,
	kTrainStop,
	kTrainDeparture,
};

#endif // !Event