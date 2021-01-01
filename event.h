/*!
	@author Formaggio Alberto
*/
#include "train.h"
#include "station.h"

#ifndef Event_h
#define Event_h
enum class EventType
{
	kTrainRequest,
	kStationAnswer,
	kTrainStop,
	kTrainDeparture,
};

class Event
{
public:
	Event(EventType e_type, int time, Train& train, Station& st);
	int GetTime() const;
	const Train& GetTrain() const;
	EventType GetType() const;
	const Station& GetStation() const;

private:
	EventType type_;
	int time_;
	Train* train_;
	Station* station_;
};


#endif // !Event