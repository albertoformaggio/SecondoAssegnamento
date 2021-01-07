/*!
	@author Formaggio Alberto
*/

#include <stdexcept>

#ifndef Event_h
#define Event_h

class Train;
class Station;

class Event
{
public:
	inline int GetTime() const { return time_; }
	inline Train* GetTrain() const { return train_; }
	inline Station* GetStation() const { return station_; }
	void SetTime(int time);
	virtual void performAction() = 0;

protected:
	Event(int time, Train* train, Station* station) : time_{ time }, train_{ train }, station_{ station } {}		//Da aggiungere controlli per evitare che siano nullptr

private:
	int time_;
	Train* train_;		//forse unique_ptr ?
	Station* station_;
};

/*class PlatformRequest : public Event
{
public:
	void performAction() override;
};

class StationAnswer : public Event
{
public:
	void performAction() override;
};*/

class TrainStop : public Event
{
public:
	void performAction() override {}
	TrainStop(int time, Train* train, Station* station) : Event(time, train, station) { }
};

/*class TrainDeparture : public Event
{
public:
	void performAction() override;
};*/

#endif // !Event