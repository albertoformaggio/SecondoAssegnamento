#include "event.h"
#include "train.h"
#include "station.h"
#include <vector>
#include <string>

#ifndef controller_h
#define controller_h

class Controller
{
public:
	Controller(std::string line_descr, std::string timetable);


private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);

	std::vector<Station> stations_;
	std::vector<Train> trains_;
	priority_queue<Event> events_;		//Pensa se è meglio usare pq o vector
};

#endif // !controller_h