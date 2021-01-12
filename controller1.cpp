/*
	@author Anna Scarpa Falce
*/

#include "controller.h"
#include "station.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

int Controller::getAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, Train* t, int delay_time)
{
	const int minPerHours = 60;

	if (time_leaving < 0 || delay_time < 0)
		return -1;

	int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));
	int distance = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin) - 2 * distanceFromPark; //funzione per avere dist da parcheggio(5);
	int minimumTime = (int)(((double)distance / t->max_speed) * minPerHours) + timeAtFixedSpeed + delay_time + t->getDelay();
	
	if (time_arrival - time_leaving < minimumTime)
		time_arrival = minimumTime + time_leaving;

	int deltaT = time_arrival - time_leaving;
	int time = deltaT - t->getDelay() - timeAtFixedSpeed;
	int v = (int)(distance / time);

	return v;
}

void Controller::handleTrainDeparture(std::vector<Event>::iterator cur)
{
	int departureTime = CheckDeparture(cur);
	if (cur->GetTime() != departureTime)
		cur->GetTrain()->editDelay(departureTime - cur->GetTime());
	
	int minPerHours = 60;
	int maxTime = distanceFromPark / speedInStation * minPerHours + distanceFromPark * minPerHours;
	
	Train* trainOnTrak = nullptr;
	int trainTimeLeaving = 0;
	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].GetStation() == cur->GetStation() && events_[i].GetType() == EventType::TrainDeparture
			&& events_[i].GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin
			&& events_[i].GetTime() < cur->GetTime() && events_[i].GetTime() > maxTime)
		{

			trainOnTrak = events_[i].GetTrain();
			trainTimeLeaving = events_[i].GetTime();
		}
	}
	int delay = 0;
	int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));
	if (trainOnTrak != nullptr)
	{
		int deltaT = cur->GetTime() - trainTimeLeaving;
		delay = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / trainOnTrak->getSpeed()) * minPerHours)) + (timeAtFixedSpeed - deltaT);
	}
	Station* to = GetNextStation(cur->GetStation(), cur->GetTrain());
	int timeArriving;
	vector<Event> relatedToTrain = GetEventsRelatedTo(cur->GetTrain());

	for (int i = 0; i < relatedToTrain.size(); i++)
		if (relatedToTrain[i].GetStation() == to && events_[i].GetType() == EventType::TrainStop)
		{
			timeArriving = relatedToTrain[i].GetTime();
		}
	cur->GetTrain()->editDelay(delay);

	int v = getAverageSpeed(*cur->GetStation(), *to, cur->GetTime() + delay, timeArriving, cur->GetTrain(), 0);
	if (trainOnTrak != nullptr && v > trainOnTrak->getSpeed())
		v = trainOnTrak->getSpeed();
	cur->GetTrain()->setSpeed(v); 

	//generazione richiesta di binario per la stazione successiva
	int distance = to->kDistanceFromOrigin - cur->GetStation()->kDistanceFromOrigin - 25;
	int timeBeforePlatformRequest = static_cast<int>(round((2 * static_cast<double>(distance) / v) * minPerHours));
	Event e(timeBeforePlatformRequest + timeAtFixedSpeed, cur->GetTrain(), to, EventType::PlatformRequest);
	events_.push_back(e);

	int hour = (cur->GetTime() + cur->GetTrain()->getDelay()) / minPerHours;
	int minute = (cur->GetTime() + cur->GetTrain()->getDelay()) % minPerHours;
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' partito dalla stazione di ";
	cout << cur->GetStation()->st_name << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	cout << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;
}

void Controller::handleArrivalToPark(std::vector<Event>::iterator cur)
{
	int minPerHours = 60;
	cur->GetStation()->addParkedTrain(*cur->GetTrain());
	int hour = (cur->GetTrain()->getDelay()) / minPerHours;
	int minute = (cur->GetTrain()->getDelay()) % minPerHours;
	
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' arrivato al parcheggio della stazione di ";
	cout << cur->GetStation()->st_name;
	cout << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	cout << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "con " << cur->GetTrain()->getDelay() << " minuti di ritardo." << endl;
	
	vector<int> v;
	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].GetType() == EventType::LeavePark && events_[i].GetStation() == cur->GetStation() &&
			cur->GetTrain()->startFromOrigin == events_[i].GetTrain()->startFromOrigin)
		{
			v.push_back(events_[i].GetTime());
		}
	}
	auto minmax = minmax_element(v.begin(), v.end());
	int latestDeparture = *minmax.second;
	cur->GetTrain()->editDelay(cur->GetTime() - latestDeparture);

	Event e(latestDeparture+1, cur->GetTrain(), cur->GetStation(), EventType::LeavePark);
	events_.push_back(e);
}

void Controller::handleParkLeaving(std::vector<Event>::iterator cur)
{
	const int minPerHours = 60;
	int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));
	int timeAtStation = cur->GetTime() + timeAtFixedSpeed;
	
	if (cur->GetStation()->getParkedTrain()->identifying_number == cur->GetTrain()->identifying_number)
	{
		bool start = false;
		vector<int> v;

		for (int i = 0; i < events_.size(); i++)
		{
			if (events_[i].GetType() == EventType::TrainDeparture
				&& events_[i].GetStation() == cur->GetStation()
				&& events_[i].GetTime() >= timeAtStation
				&& events_[i].GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin)
			{
				v.push_back(events_[i].GetTime());
			}
			else if (events_[i].GetType() == EventType::TrainDeparture
				&& events_[i].GetStation() == cur->GetStation()
				&& events_[i].GetTime() < timeAtStation
				&& events_[i].GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin)
			{
				cur->GetStation()->removeParkedTrain();
				int hour = (cur->GetTime() + cur->GetTrain()->getDelay()) / 60;
				int minute = (cur->GetTime() + cur->GetTrain()->getDelay()) / 60;
				cout << "Il treno " << cur->GetTrain()->identifying_number << " e' uscito dal parcheggio della stazione di ";
				cout << cur->GetStation()->st_name;
				//cout << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
				//cout << std::setfill('0') << std::setw(2) << minute << endl;
				//cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;
				return;
			}
		}
		auto minmax = minmax_element(v.begin(), v.end());
		int firstLeaving = *minmax.first;
		cur->GetTrain()->editDelay(firstLeaving - cur->GetTime());

		//aggiorno evento leavePark di quelli dello stesso parcheggio con quel ritardo+1 (per sicurezza)
		for (int i = 0; i < events_.size(); i++)
		{
			if (events_[i].GetType() == EventType::LeavePark
				&& events_[i].GetStation() == cur->GetStation()
				&& events_[i].GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin)
			{
				events_[i].GetTrain()->editDelay(firstLeaving + 1);
			}
		}
	}
	cur->GetStation()->removeParkedTrain();
	int hour = (cur->GetTime() + cur->GetTrain()->getDelay()) / 60;
	int minute = (cur->GetTime() + cur->GetTrain()->getDelay()) % 60;
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' uscito dal parcheggio della stazione di ";
	cout << cur->GetStation()->st_name;
	//cout << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	//cout << std::setfill('0') << std::setw(2) << minute << endl;
	//cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;
}