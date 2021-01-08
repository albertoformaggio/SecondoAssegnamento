/*!
	@author Formaggio Alberto
*/

#ifndef controller_h
#define controller_h

#include "station.h"
#include "train.h"
#include "HSTrain.h"
#include "HSTrainSuper.h"
#include "RegionalTrain.h"
#include "event.h"
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
	void printEvents();		//SOLO PER DEBUGGING

private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);
	void CheckTimetable();
	void CheckStations();
	void EraseEventsRelatedTo(Station* ev);
	std::vector<Event*> GetEventsRelatedTo(Train* tr);
	void handleEvent(TrainStop& ts);		//Non può funzionare così se passo puntatore a Event, devo per forza dynamic_cast, altrimenti si cambia totalmente approccio
	void handleEvent(PlatformRequest& pr);
	void handleEvent(TrainDeparture& td);

	std::vector<Station*> stations_;		//uso pointer normali perchè tanto il distruttore è già definito dalle classi Station e Train
	std::vector<Train*> trains_;
	std::vector<Event*> events_;		//Pensa se è meglio usare pq o vector. Potrei usare 2 vector: uno di eventi svolti e uno di eventi da svolgere
};

#endif // !controller_h