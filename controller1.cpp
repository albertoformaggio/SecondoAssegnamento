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
	int v = (int)(round(((double)distance / time) * minPerHours));

	return v;
}

void Controller::handleTrainDeparture(std::vector<Event>::iterator cur)
{
	int departureTime = CheckDeparture(cur);
	if ((cur->GetTime() + cur->GetTrain()->getDelay()) != departureTime)
	{
		cur->GetTrain()->editDelay(departureTime - cur->GetTime());
		return;
	}
	
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
	cur->GetTrain()->editDelay(delay);
	if (delay != 0)
		return;
	Station* to = GetNextStation(cur->GetStation(), cur->GetTrain());
	int timeArriving;
	vector<Event> relatedToTrain = GetEventsRelatedTo(cur->GetTrain());

	for (int i = 0; i < relatedToTrain.size(); i++)
		if (relatedToTrain[i].GetStation() == to && events_[i].GetType() == EventType::TrainStop)
		{
			timeArriving = relatedToTrain[i].GetTime();
		}
	

	int v = getAverageSpeed(*cur->GetStation(), *to, cur->GetTime() + delay, timeArriving, cur->GetTrain(), 0);
	if (trainOnTrak != nullptr && v > trainOnTrak->getSpeed())
		v = trainOnTrak->getSpeed();
	cur->GetTrain()->setSpeed(v); 

	//generazione richiesta di binario per la stazione successiva
	int distance = to->kDistanceFromOrigin - cur->GetStation()->kDistanceFromOrigin - 25;
	int timeBeforePlatformRequest = static_cast<int>(round((2 * static_cast<double>(distance) / v) * minPerHours));
	Event e(timeBeforePlatformRequest + timeAtFixedSpeed, cur->GetTrain(), to, EventType::PlatformRequest);

	int hour = (cur->GetTime() + cur->GetTrain()->getDelay()) / minPerHours;
	int minute = (cur->GetTime() + cur->GetTrain()->getDelay()) % minPerHours;
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' partito dalla stazione di ";
	cout << cur->GetStation()->st_name << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	cout << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "accumulando un ritardo di " << cur->GetTrain()->getDelay() << " minuti." << endl;

	events_.push_back(e);

}

void Controller::handleArrivalToPark(std::vector<Event>::iterator cur)
{
	//stampa degll'arrivo inparcheggio
	int minPerHours = 60;
	cur->GetStation()->addParkedTrain(*cur->GetTrain());
	int hour = (cur->GetTrain()->getDelay()) / minPerHours;
	int minute = (cur->GetTrain()->getDelay()) % minPerHours;
	
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' arrivato al parcheggio della stazione di ";
	cout << cur->GetStation()->st_name;
	//cout << " alle ore " << std::setfill('0') << std::setw(2) << hour << ":";
	//cout << std::setfill('0') << std::setw(2) << minute << endl;
	//cout << "con " << cur->GetTrain()->getDelay() << " minuti di ritardo." << endl;
	
	//vettore di orari di uscita dal parcheggio dei treni parcheggiati
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
	//prendo l'rario di uscita di quello davanti a me e aggiungo al treno un ritardo pari a quanto deve
	//aspettare affinchè sia il primo dei treni parcheggiati
	cur->GetTrain()->editDelay(latestDeparture - cur->GetTime());

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
		//vettore degli orari dei treni che partirebbero dopo l'arrivo del treno in stazione
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
		}

		if (!v.empty())
		{
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