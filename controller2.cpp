/* @author Michele Rieppi */

#include "controller.h"
void Controller::requestPlatform(std::vector<Event>::iterator cur) { //richiesta di un binario alla stazione successiva (che so già)

	const int minPerHours = 60;
	const int distanceToPark = 15;	//distanza da percorrere in km
	const int timeAtFixedSpeed = static_cast<int>(round((2 * static_cast<double>(distanceFromPark) / speedInStation) * minPerHours));	//Tempo per tratto lento 

	std::cout << "Il treno" << cur->GetTrain()->identifying_number << " richiede alla stazione " << cur->GetStation()->st_name << " un binario alle ore " << cur->GetTime();


	int time = static_cast<int>(round(static_cast<double>(distanceToPark) / cur->GetTrain()->getSpeed() * minPerHours)); //Caso in cui la stazione successiva è stazione principale
	Platform* p = nullptr;
	if (dynamic_cast<mainStation*>(cur->GetStation()) != nullptr)
		p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);					//Creo un binario generico per controllare che sia standard
	if (dynamic_cast<parkPlatform*>(p) != nullptr)
		Event park(cur->GetTime() + time, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
	Event stop(cur->GetTime() + distanceToPark + timeAtFixedSpeed, cur->GetTrain(), cur->GetStation(), EventType::TrainStop);	//Caso in cui ho binario standard creo l'evento di fermata del treno

	if (dynamic_cast<localStation*>(cur->GetStation()) != nullptr)							//Nel caso di una stazione locale
		if (dynamic_cast<RegionalTrain*>(cur->GetTrain()) != nullptr) {						//Nel caso in cui il treno sia regionale controllo se c'è il binario per fermarsi
			p = cur->GetStation()->getStandardPlatform(cur->GetTrain()->startFromOrigin);	//Controllo che ci sia un binario standard disponibile
			if (dynamic_cast<parkPlatform*>(p) != nullptr)									//Se non ho binari disponibili	
				Event park(cur->GetTime() + time, cur->GetTrain(), cur->GetStation(), EventType::ArriveToPark);	//Caso in cui ho un binario di parcheggio creo l'evento di parcheggio
			Event stop(cur->GetTime() + distanceToPark + timeAtFixedSpeed, cur->GetTrain(), cur->GetStation(), EventType::TrainStop);	//Caso in cui ho binario standard creo l'evento di fermata del treno
		}

	//Prendo il binario di transito se il treno non è regionale

}
Platform* Controller::requestPlatform(std::vector<Event>::iterator cur) {
	if()
}