/*!
	@author Formaggio Alberto
*/

#include "event.h"
#include "train.h"
#include "station.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

#ifndef controller_h
#define controller_h

class Controller
{
public:
	class FileNotFoundException { };
	Controller(std::string line_descr, std::string timetable);


private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);
	//void GetTimes(std::istringstream ss, int st_index, int train_type);

	std::vector<Station*> stations_;		//uso pointer normali perchè tanto il distruttore è già definito dalle classi Station e Train
	std::vector<Train*> trains_;
	std::vector<Event> events_;		//Pensa se è meglio usare pq o vector
};

#endif // !controller_h