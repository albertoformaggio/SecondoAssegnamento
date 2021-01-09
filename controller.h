/*!
	@author Formaggio Alberto
*/

#ifndef controller_h
#define controller_h

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

class Train;
class Event;
class Station;

class Controller
{
public:
	class FileNotFoundException { };
	Controller(std::string line_descr, std::string timetable);
	static constexpr int kMinDistanceBetweenStations = 20;
	void printEvents();		//SOLO PER DEBUGGING

private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);
	void CheckTimetable();
	void CheckStations();
	void EraseEventsRelatedTo(Station* ev);
	int getAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, Train* t, int delay_time = 0);
	std::vector<Event> GetEventsRelatedTo(Train* tr);
	bool EventIsLessThan(Event first, Event other);
	void handleTrainStop(Event& ts);		//Non può funzionare così se passo puntatore a Event, devo per forza dynamic_cast, altrimenti si cambia totalmente approccio

	std::vector<Station*> stations_;		//uso pointer normali perchè tanto il distruttore è già definito dalle classi Station e Train
	std::vector<Train*> trains_;
	std::vector<Event> events_;		//Pensa se è meglio usare pq o vector.
};

#endif // !controller_h