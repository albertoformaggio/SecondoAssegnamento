/* @author Michele Rieppi */

#include "controller.h"
#include <iomanip>
//DEVI AGGIUNGERE I GETDELAY() AD i->GetTime() e cur->GetTime()

void Controller::handlePlatformRequest(std::vector<Event>::iterator cur) { //richiesta di un binario alla stazione successiva (che so già)

	const int minPerHours = 60;
	const int distanceToPark = 15;	//distanza da percorrere in km
	const int timeAtFixedSpeed = static_cast<int>(round((static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));	//Tempo per tratto lento 

	std::cout << "Il treno " << cur->GetTrain()->identifying_number << " richiede alla stazione " << cur->GetStation()->st_name << cur->GetTrain()->getSpeed() <<std::endl;


	int time_to_park = static_cast<int>(round(static_cast<double>(distanceToPark) / cur->GetTrain()->getSpeed() * minPerHours)); //Caso in cui la stazione successiva è stazione principale
	Platform* p = nullptr;
	if (dynamic_cast<mainStation*>(cur->GetStation()) != nullptr)
		p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);					//Creo un binario generico per controllare che sia standard
	if (dynamic_cast<parkPlatform*>(p) != nullptr) {
		Event park(cur->GetTime() + time_to_park, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
		events_.push_back(park);
	}


	if (dynamic_cast<localStation*>(cur->GetStation()) != nullptr) {							//Nel caso di una stazione locale
		if (dynamic_cast<RegionalTrain*>(cur->GetTrain()) != nullptr) {						//Nel caso in cui il treno sia regionale controllo se c'è il binario per fermarsi
			p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);	//Controllo che ci sia un binario standard disponibile
			if (dynamic_cast<parkPlatform*>(p) != nullptr) {									//Se non ho binari disponibili	
				Event park(cur->GetTime() + time_to_park, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
				events_.push_back(park);
			}
		}
		else {																								//Altrimenti transito fino alla prossima stazione, devo capire quando farò richiesta e adatterò la mia velocità
			Station* nextStation = GetNextStation(cur->GetStation(), cur->GetTrain());						//Trovo la prossima stazione
			/*
			Event* last_event = nullptr;
			for (auto i = events_.begin(); i < cur; i++)												//Ciclo sugli eventi
				if (cur->GetStation() == i->GetStation() && i->GetType() == EventType::TrainDeparture) {	//Se ci sono eventi di partenza dalla stazione in cui sto per passare
					last_event = &(*i);																		//Se trovo un treno che mi dà problemi me lo salvo
				}
			for (auto i = events_.begin(); i < cur; i++) {												//Ciclo sugli eventi
				if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr && i->GetType() == EventType::PlatformRequest && cur->GetStation() == i->GetStation()) {
					if (last_event == nullptr || last_event->GetTime() < i->GetTime())						//Last event contiene ultimo evento relativo a un treno regionale, i punta a un alta velocità
						last_event = &(*i);
				}
			}
			if (last_event != nullptr) {																//Guardo se l'ultimo treno che è passato per questa stazione (se esiste) è già arrivato alla stazione successiva
				bool found = false;
				for (auto i = events_.begin(); i < cur; i++) {
					if (next_station == i->GetStation() && i->GetType() == EventType::PlatformRequest && i->GetTrain() == last_event->GetTrain()) {
						found = true;
					}
				}
				if (!found)
					last_event = nullptr;
			}

			int arrival_time = -1;
			int speed = -1;
			if (dynamic_cast<mainStation*>(next_station) != nullptr)
			{
				int distance = cur->GetStation()->kDistanceFromOrigin + next_station->kDistanceFromOrigin + 20;
				arrival_time = 12345; //Da modificare

				int deltaT = arrival_time - cur->GetTime() - timeAtFixedSpeed;
				int time = deltaT - cur->GetTrain()->getDelay() - timeAtFixedSpeed;
				speed = (int)(distance / time);
			}
			else
			{
				int distance = cur->GetStation()->kDistanceFromOrigin + next_station->kDistanceFromOrigin + 20;
				arrival_time = (int)(((double)distance / cur->GetTrain()->max_speed) * minPerHours) + cur->GetTrain()->getDelay();

				int deltaT = arrival_time - cur->GetTime();
				int time = deltaT - cur->GetTrain()->getDelay();
				speed = (int)(distance / time);
			}

			if (last_event != nullptr)
				cur->GetTrain()->setSpeed(last_event->GetTrain()->getSpeed());
			else
				cur->GetTrain()->setSpeed(speed);
				
			int timeOnTrack = static_cast<int>(round(static_cast<double>(abs(cur->GetStation()->kDistanceFromOrigin - next_station->kDistanceFromOrigin)) / cur->GetTrain()->getSpeed() * minPerHours));
			const int delay = timeOnTrack - arrivalTime;
			cur->GetTrain()->editDelay(delay);	//Se la differenza è negativa, viene aggiunto un ritardo negativo, cioè il treno recupera ritardo 
			*/
		//Ora ti manca da calcolare il tempo che ci metti per arrivare a fare la nuova richiesta
		//La distanza da questa stazione alla prossima richiesta è di: distanza tra le stazioni (entrambi fanno la richiesta quando si trovano 20 kilometri prima
			int time_until_request = static_cast<int>(round(static_cast<double>(abs(cur->GetStation()->kDistanceFromOrigin - nextStation->kDistanceFromOrigin)) / cur->GetTrain()->getSpeed() * minPerHours));
			Event request(cur->GetTime() + time_until_request, cur->GetTrain(), nextStation, EventType::PlatformRequest);
			events_.push_back(request);
		}
	}

	
}