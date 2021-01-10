/*
	@author Anna Scarpa Falce
*/

#include "controller.h"
#include "station.h"
#include <vector>

int Controller::getAverageSpeed(const Station& from, const Station& to, int time_leaving, int& time_arrival, Train* t, int delay_time)
{
	const int minPerHours = 60;

	if (time_leaving < 0 || delay_time < 0)
		return -1;

	int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));
	int distance = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin) - 2 * distanceFromPark; //funzione per avere dist da parcheggio(5);
	int minimumTime = (int)(distance / t->max_speed) * minPerHours + timeAtFixedSpeed + delay_time + t->getDelay();
	
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

void Controller::handleParking(std::vector<Event>::iterator cur)
{
	const int minPerHours = 60;
	Train* t;
	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].GetType() == EventType::PlatformRequest && events_[i].GetTrain()->identifying_number == cur->GetTrain()->identifying_number && events_[i].GetStation() == cur->GetStation())
			t = events_[i].GetTrain();
	}
	int speed = t->getSpeed();
	int distance = 15;			//distanza richiesta-parcheggio
	int time = static_cast<int>(round(static_cast<double>(distance / speed)*minPerHours));
}