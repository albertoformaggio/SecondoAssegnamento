/* @author Michele Rieppi */

#include "controller.h"
void Controller::handlePlatformRequest(std::vector<Event>::iterator cur) { //richiesta di un binario alla stazione successiva (che so gi�)

	const int minPerHours = 60;
	const int distanceToPark = 15;	//distanza da percorrere in km
	const int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));	//Tempo per tratto lento 

	std::cout << "Il treno" << cur->GetTrain()->identifying_number << " richiede alla stazione " << cur->GetStation()->st_name << " un binario alle ore " << cur->GetTime();


	int time = static_cast<int>(round(static_cast<double>(distanceToPark) / cur->GetTrain()->getSpeed() * minPerHours)); //Caso in cui la stazione successiva � stazione principale
	Platform* p = nullptr;
	if (dynamic_cast<mainStation*>(cur->GetStation()) != nullptr)
		p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);					//Creo un binario generico per controllare che sia standard
	if (dynamic_cast<parkPlatform*>(p) != nullptr) {
		Event park(cur->GetTime() + time, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
		events_.push_back(park);
	}
	

	if (dynamic_cast<localStation*>(cur->GetStation()) != nullptr) {							//Nel caso di una stazione locale
		if (dynamic_cast<RegionalTrain*>(cur->GetTrain()) != nullptr) {						//Nel caso in cui il treno sia regionale controllo se c'� il binario per fermarsi
			p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);	//Controllo che ci sia un binario standard disponibile
			if (dynamic_cast<parkPlatform*>(p) != nullptr) {									//Se non ho binari disponibili	
				Event park(cur->GetTime() + time, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
				events_.push_back(park);
			}
		}
		else {
			Station* next_station = GetNextStation(cur->GetStation(), cur->GetTrain());						//Trovo la prossima stazione
			Train* last_train = nullptr;
			for (auto i = cur - 1; i >= events_.begin(); i--)												//Ciclo sugli eventi
				if (cur->GetStation() == i->GetStation() && i->GetType() == EventType::TrainDeparture) {	//Se ci sono eventi di partenza dalla stazione in cui sto per passare
					last_train = i->GetTrain();
					break;
				}
			if (last_train != nullptr) {
				bool found = false;
				for (auto i = cur - 1; i >= events_.begin(); i--) {
					if (next_station == i->GetStation() && i->GetType() == EventType::PlatformRequest && i->GetTrain() == last_train) {
						found = true;
						break;
					}
				}
				if (!found)
					last_train = nullptr;
			}
		}
	}
	

}