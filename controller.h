﻿/*!
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
#include "localStation.h"
#include "mainStation.h"
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
	void printEvents();	
	~Controller();

private:
	void GetStations(std::string line_descr);
	void GetTimetable(std::string timetable);
	void CheckTimetable();
	void CheckStations();
	void EraseEventsRelatedTo(Station* ev);
	int getAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, Train* t, int delay_time = 0);
	std::vector<Event*> GetEventsRelatedTo(Train* tr);
	void handlePlatformRequest(std::vector<Event>::iterator cur);
	void handleTrainStop(std::vector<Event>::iterator cur);	
	bool handleTrainDeparture(std::vector<Event>::iterator cur);
	void handleArrivalToPark(std::vector<Event>::iterator cur);
	void handleParkLeaving(std::vector<Event>::iterator cur);
	int CheckDeparture(std::vector<Event>::iterator cur);
	Station* GetNextStation(Station* current_station, Train* tr);
	

	std::vector<Station*> stations_;		
	std::vector<Train*> trains_;
	std::vector<Event> events_;		
	const int min_wait = 5;
	const int distanceFromPark = 5;
	const int speedInStation = 80;
	const int kMinDistanceBetweenTrains = 10;
};

#endif // !controller_h