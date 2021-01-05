/*!
	@author Formaggio Alberto
*/

#ifndef controller_h
#define controller_h

#include "event.h"
#include "train.h"
#include "HSTrain.h"
#include "HSTrainSuper.h"
#include "RegionalTrain.h"
#include "station.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

class Controller
{
public:
	class FileNotFoundException { };
	Controller(std::string line_descr, std::string timetable);
	static constexpr int kMinDistanceBetweenStations = 20;

private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);
	void CheckValues();
	void EraseEventsRelatedTo(Station* ev);

	std::vector<Station*> stations_;		//uso pointer normali perchè tanto il distruttore è già definito dalle classi Station e Train
	std::vector<Train*> trains_;
	std::vector<Event*> events_;		//Pensa se è meglio usare pq o vector
};

#endif // !controller_h