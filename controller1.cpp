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

	int timeAtFixedSpeed = (2 * distanceFromPark / speedInStation) * minPerHours;
	int distance = abs(from.kDistanceFromOrigin - to.kDistanceFromOrigin) - 2 * distanceFromPark; //funzione per avere dist da parcheggio(5);
	int minimumTime = (int)(distance / t->max_speed) * minPerHours + timeAtFixedSpeed + delay_time + t->getDelay();
	
	if (time_arrival - time_leaving < minimumTime)
		time_arrival = minimumTime;

	int deltaT = time_arrival - time_leaving;
	int time = deltaT - t->getDelay() - timeAtFixedSpeed;
	int v = (int)(distance / time);

	return v;
}

void Controller::handleTrainDeparture(std::vector<Event>::iterator cur)
{
	if (dynamic_cast<mainStation*>(cur->GetStation()) != nullptr)
	{
		//vettore dei treni papabili per la partenza
		std::vector<Train*> t;
		for (int i = 0; i < events_.size(); i++)
		{
			//se lo stesso tipo di evento ha stessa stazione e un orarrio compreso tra +-5 minuti da cur allora è treno valido
			if (events_[i].GetType() == cur->GetType() && events_[i].GetStation() == cur->GetStation() && (events_[i].GetTime() < cur->GetTime() + 5 || events_[i].GetTime() > cur->GetTime() - 5))
				t.push_back(events_[i].GetTrain());
			//va fatto check se la piattaforma è libera
			if (events_[i].GetType() == PlatformRequest && events_[i].GetStation() == cur->GetStation() && (events_[i].GetTime() < cur->GetTime() + 5 || events_[i].GetTime() > cur->GetTime() - 5))
				t.push_back(events_[i].GetTrain());
		}
		Train* readyForDeparture = t[0];
		for (int i = 1; i < t.size(); i++)
		{
			//prendo il treno che deve arrivare alla stazione successiva prima, ovvero quello che avrà anche velocita' massima
			if(getTimeNextStation(t[i], cur->GetStation()))

			//se arrivano allo stesso momento allora guardo ritardo
		}
		//se avessi la direzione del treno(mem nell'evento) potrei sapere qual e' la stazine successiva
	}
}