/*!
	@author Formaggio Alberto
*/

#ifndef Event_h
#define Event_h

class Train;
class Station;

enum class EventType
{
	PlatformRequest,
	TrainStop,
	TrainDeparture
};

class Event
{
public:
	inline int GetTime() const { return time_; }
	inline Train* GetTrain() const { return train_; }
	inline Station* GetStation() const { return station_; }
	inline EventType GetType() const { return type_; }
	void SetTime(int time);
	Event(int time, Train* train, Station* station, EventType type) : time_{ time }, train_{ train }, station_{ station }, type_{ type } {}		//Da aggiungere controlli per evitare che siano nullptr	

private:
	int time_;
	Train* train_;		//forse unique_ptr ?
	Station* station_;
	EventType type_;
};

#endif // !Event