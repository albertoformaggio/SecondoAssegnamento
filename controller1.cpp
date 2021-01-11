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

/*void Controller::handleTrainDeparture(std::vector<Event>::iterator cur)
{
	if (dynamic_cast<mainStation*>(cur->GetStation()) != nullptr)
	{
		//vettore dei treni papabili per la partenza
		std::vector<Train*> t;
		for (int i = 0; i < events_.size(); i++)
		{
			//se lo stesso tipo di evento ha stessa stazione e un orarrio compreso tra +-5 minuti da cur allora � treno valido
			if (events_[i].GetType() == cur->GetType() && events_[i].GetStation() == cur->GetStation() && (events_[i].GetTime() < cur->GetTime() + 5 || events_[i].GetTime() > cur->GetTime() - 5))
				t.push_back(events_[i].GetTrain());
			//va fatto check se la piattaforma � libera
			if (events_[i].GetType() == EventType::PlatformRequest && events_[i].GetStation() == cur->GetStation() && (events_[i].GetTime() < cur->GetTime() + 5 || events_[i].GetTime() > cur->GetTime() - 5))
				t.push_back(events_[i].GetTrain());
		}
		Train* readyForDeparture = t[0];
		for (int i = 1; i < t.size(); i++)
		{
			//prendo il treno che deve arrivare alla stazione successiva prima, ovvero quello che avr� anche velocita' massima

			//se arrivano allo stesso momento allora guardo ritardo
		}
		//se avessi la direzione del treno(mem nell'evento) potrei sapere qual e' la stazine successiva
	}
}*/

void Controller::handleArrivalToPark(std::vector<Event>::iterator cur)
{
	int hour = cur->GetTime() / 60;
	int minute = cur->GetTime() % 60;
	
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' arrivato al parcheggio della stazione di ";
	cout << cur->GetStation()->st_name << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
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
	sort(events_.begin(), events_.end());
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
				int hour = cur->GetTime() / 60;
				int minute = cur->GetTime() % 60;
				cout << "Il treno " << cur->GetTrain()->identifying_number << " e' uscito dal parcheggio della stazione di ";
				cout << cur->GetStation()->st_name << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
				cout << std::setfill('0') << std::setw(2) << minute << endl;
				cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;
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
				events_[i].SetTime(events_[i].GetTime() + firstLeaving + 1);
				events_[i].GetTrain()->editDelay(firstLeaving + 1);
			}
		}
	}
	
	int hour = cur->GetTime() / 60;
	int minute = cur->GetTime() % 60;
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' uscito dal parcheggio della stazione di ";
	cout << cur->GetStation()->st_name << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	cout << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;

	sort(events_.begin(), events_.end());

}
