/*!
	@author Formaggio Alberto
*/
#include "controller.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

Controller::Controller(string line_descr, string timetable)
{
	GetStations(line_descr);
	GetTimetable(timetable);
	CheckStations();
	CheckTimetable();
}

void Controller::GetStations(string line_descr)
{
	ifstream lines_file;
	lines_file.open(line_descr);

	if (!lines_file.is_open())
	{
		cerr << "The file named: " << line_descr << " doesn't exist";
		//line_file.close(); Se lo lascio potrebbe lanciare eccezione,           DA TESTARE 
		throw FileNotFoundException();
	}

	//Gestisco la stazione di origine in modo "speciale", ha parametri diversi.

	string station_name;
	string line;
	getline(lines_file, line);
	istringstream ss(line);
	int distance = 0;
	ss >> station_name;

	//SCELTA DI PROGETTO:
	//La stazione di origine, avendo solamente il nome e nessuna informazione sul suo tipo, viene considerata principale
	stations_.push_back(new mainStation(distance, station_name));

	int station_type_number = 0;
	while (!lines_file.eof())
	{
		getline(lines_file, line);
		istringstream ss2(line);

		string tmp;
		ss2 >> station_name;
		while (ss2 >> tmp)
		{
			if (isdigit(tmp.at(0)))
				break;
			station_name += " " + tmp;
		}
		//Quando il ciclo � terminato, in tmp � presente la prima cifra della riga, ovvero il tipo di stazione 
		station_type_number = stoi(tmp);

		ss2 >> distance;

		if (station_type_number == 0)
			stations_.push_back(new mainStation(distance, station_name));
		else
			stations_.push_back(new localStation(distance, station_name));
	}
	sort(stations_.begin(), stations_.end(), isFartherThan);
	lines_file.close();
}




void Controller::GetTimetable(string timetable)
{
	ifstream time_file;
	time_file.open(timetable);

	if (!time_file.is_open())
	{
		cerr << "The file named: " << timetable << "doesn't exist";
		throw FileNotFoundException();
	}

	int train_id, first_station, train_type, time;
	const int reg = 1;
	const int hs = 2;
	const int hs_super = 3;
	while (!time_file.eof())
	{
		string line;
		getline(time_file, line);
		istringstream ss(line);

		ss >> train_id >> first_station >> train_type;
		bool from_origin = first_station == 0;
		Train* tr = nullptr;
		switch (train_type)
		{
		case reg:
			tr = new RegionalTrain(train_id, from_origin);
			break;
		case hs:
			tr = new HSTrain(train_id, from_origin);
			break;
		case hs_super:
			tr = new HSTrainSuper(train_id, from_origin);

			break;
		}

		if (ss.eof()) //Se il file non ha nemmeno l'orario di partenza, ignoro il treno passato
		{
			cerr << "Il treno " << train_id << " non ha un orario di partenza: non puo' esistere" << endl;
			delete tr;
		}
		else
		{
			trains_.push_back(tr);
			bool forward = first_station == 0;
			const int delay_time = 10;
			bool first_insertion = true;
			for (int i = 0; i < stations_.size(); i++)
			{
				const int x = forward ? i : (stations_.size() - 1) - i;
				Station* current_station = stations_.at(x);
				if (train_type == reg || (train_type != reg && dynamic_cast<localStation*>(current_station) == nullptr))		//COME FARE QUESTO CHECK?		Se il treno non � regionale e la stazione � locale, allora non ci sar� nessun evento di fermata del treno a tale stazione
				{
					int time;
					if (!(ss >> time))
					{
						time = -1;
						Event last = events_.at(events_.size() - 1);	//Ottengo l'ultimo evento di fermata inserito
						const Station* lastStation = last.GetStation();		//manca copy constructor/move constructor						
						getAverageSpeed(*lastStation, *current_station, last.GetTime(), time, tr, delay_time);		//Creare un metodo nella classe TRAIN che date 2 distanze, un tempo di partenza, un tempo di arrivo e un tempo di ritardo ritorni la distanza. 
																																					//Se l'orario di partenza non � valido (cio� negativo), calcolarlo usando il minor tempo possibile pi� ritardo (magari il ritardo lo metti con parametro di default = 0)
					}

					if (first_insertion)	//Il primo orario della lista sarà un evento di partenza e non di stop. Eseguo l'if perchè non è detto che la prima stazione sia principale
					{
						Event e(time, tr, stations_.at(x), EventType::TrainDeparture);
						events_.push_back(e);
						first_insertion = false;
					}
					else
					{
						Event e(time, tr, stations_.at(x), EventType::TrainStop);
						events_.push_back(e);						
					}					
				}
			}
		}
	}
	time_file.close();
}

void Controller::CheckStations()
{
	auto prev = stations_.begin();
	auto cur = prev + 1;
	while (cur != stations_.end())
	{
		int distance = abs((**cur).kDistanceFromOrigin - (**prev).kDistanceFromOrigin);
		if (distance <= kMinDistanceBetweenStations)
		{
			EraseEventsRelatedTo(*cur);
			cur = stations_.erase(cur);
		}
		else
		{
			cur++;
			prev++;
		}
	}
}

void Controller::EraseEventsRelatedTo(Station* st)
{
	auto it = events_.begin();
	while (it < events_.end())
	{
		if ((*it).GetStation() == st)
			it = events_.erase(it);
		else
			it++;
	}
}

void Controller::printEvents()
{
	cout << endl << endl << "==========Inizio stampa eventi==========" << endl << endl;
	int i = 0;
	sort(events_.begin(), events_.end());
	bool increment = true;
	while(i < events_.size())
	{
		auto cur_iterator = events_.begin() + i;
		int old_train_delay = cur_iterator->GetTrain()->getDelay();	//Un treno può essere spostato nel futuro solo se il ritardo aumenta
		switch (events_[i].GetType())
		{
		case EventType::TrainStop: handleTrainStop(cur_iterator);
			break;
		case EventType::TrainDeparture: increment = handleTrainDeparture(cur_iterator);
			break;
		case EventType::PlatformRequest: handlePlatformRequest(cur_iterator);
			break;
		case EventType::ArriveToPark: handleArrivalToPark(cur_iterator);
			break;
		case EventType::LeavePark: handleParkLeaving(cur_iterator);
			break;
		}
		
		//Posso aver invalidato l'iteratore facendo push back di un evento, quindi lo ricreo.

		//Se il treno ha diminuito il suo ritardo o questo è rimasto costante, allora l'evento è accaduto e posso spostarmi avanti nella lista di eventi
		//Se invece il ritardo è aumentato, facendo il sort questo verrà spostato avanti nella lista di eventi e l'evento che arriverà nella posizione i-esima deve ancora essere eseguito:
		//non posso quindi far avanzare l'indice.
		int new_train_delay = (events_.begin() + i)->GetTrain()->getDelay();
		if (increment)
			i++;

		sort(events_.begin() + i, events_.end());
	}

	//Ciclo di stampa degli eventi creati in fase di lettura del file dopo aver controllato la timetable e che la distanza tra le stazioni fosse maggiore di 20km
	/*for (int i = 0; i < events_.size(); i++)
	{
		cout << events_[i].GetStation()->st_name << " " << events_[i].GetTrain()->identifying_number << " " << events_[i].GetTime() << endl;
	}*/
}

Controller::~Controller()
{
	for each (Train* tr in trains_)
	{
		delete tr;
	}

	for each (Station * st in stations_)
	{
		delete st;
	}
}

void Controller::CheckTimetable()
{
	for (int i = 0; i < trains_.size(); i++)
	{
		Train* tr = trains_.at(i);
		vector<Event*> ev = GetEventsRelatedTo(tr);
		for (int j = 1; j < ev.size(); j++)
		{
			int arrive_time = ev.at(j)->GetTime();
			int leave_time = ev.at(j - 1)->GetTime();
			Station* previous = ev.at(j - 1)->GetStation();

			getAverageSpeed(*previous, *(ev.at(j)->GetStation()), leave_time, arrive_time, tr);

			if (arrive_time != ev.at(j)->GetTime())
			{
				int evaluated_delay = arrive_time - ev[j]->GetTime();
				int k = j;
				for (k; k < ev.size(); k++)
				{
					int cur_time = ev[k]->GetTime();
					ev[k]->SetTime(cur_time + evaluated_delay);
				}
				cout << "Orario di arrivo del treno " << tr->identifying_number << " alla stazione " << ev[j]->GetStation()->st_name << endl;
				cout << "non compatibile con la velocita' del treno. " << k - j << " orari cambiati di conseguenza" << endl;
			}
		}
	}
}

//Il ritardo del treno va aggiunto a TUTTI gli eventi successivi quando arrivo in parcheggio => solo i parcheggi mi fanno perdere tempo rispetto alla tabella di marcia

void Controller::handleTrainStop(vector<Event>::iterator cur)
{
	//Stampo l'evento che e' appena accaduto
	int hour = (cur->GetTime() + cur->GetTrain()->getDelay()) / 60;
	hour %= 24;
	int minute = (cur->GetTime() + cur->GetTrain()->getDelay()) % 60;
	cout << "Il treno " << cur->GetTrain()->identifying_number << " e' arrivato alla stazione " << cur->GetStation()->st_name << " alle ore ";
	cout << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "con " << cur->GetTrain()->getDelay() << " minuti di ritardo." << endl;

	//Prima controlla che non sia il capolinea del treno. Ottengo l'ultima stazione della tratta secondo il senso di marcia del treno
	//Station* last_line_station = cur->GetTrain()->startFromOrigin ? stations_[stations_.size() - 1] : stations_[0];
	auto i = cur + 1;
	bool found = false;
	while (i < events_.end() && i->GetTrain() != cur->GetTrain())
		i++;

	//Se i non è la fine dell'array, c'è un altro evento da gestire di partenza
	if (i != events_.end())
	{
		int departure_time = min_wait + cur->GetTime();
		Event departure(departure_time, cur->GetTrain(), cur->GetStation(), EventType::TrainDeparture);
		events_.push_back(departure);
	}
	else
	{
		cout << "Il treno " << cur->GetTrain()->identifying_number << " e' arrivato alla fine della corsa con un ritardo di " << cur->GetTrain()->getDelay() << " minuti" << endl;
	}
}

vector<Event*> Controller::GetEventsRelatedTo(Train* tr)
{
	vector<Event*> events;
	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].GetTrain() == tr) //Confronto gli indirizzi di memoria
			events.push_back(&events_.at(i));
	}

	return events; //Costruttore di move di vector usato, non viene fatta l'intera copia
}


int Controller::CheckDeparture(vector<Event>::iterator cur)
{
	//Controlla di non essere ultima stazione della tratta

	int departure_time = cur->GetTime() + cur->GetTrain()->getDelay();
	Station* next_main_station = nullptr;
	Station* next_local_station = nullptr;
	int next_local_arrive_time = -1;
	int next_main_arrive_time = -1;
	bool found_local = false;
	bool found_main = false;
	//Cerco l'orario di arrivo di questo treno alla stazione successiva
	for (auto i = cur + 1; i < events_.end() && (!found_local || !found_main); i++)
	{
		if (i->GetTrain() == cur->GetTrain())
		{
			if (dynamic_cast<mainStation*>(i->GetStation()) != nullptr && !found_main)
			{
				next_main_arrive_time = i->GetTime() + i->GetTrain()->getDelay();
				next_main_station = i->GetStation();
				found_main = true;
			}
			else if (!found_local)
			{
				next_local_arrive_time = i->GetTime() + i->GetTrain()->getDelay();
				next_local_station = i->GetStation();
				found_local = true;
			}
		}
	}

	//Cerco l'ultimo evento di un treno regionale e non regionale che deve arrivare alla prossima stazione prima di me. Faccio un'unica scansione. 
	//Uso quindi il tempo di arrivo alla prossima stazione principale (che in genere è >= del tempo di arrivo alla prossima stazione).
	//Così facendo però potrei trovare anche un treno che arriva alla prossima stazione nel lasso di tempo next_local_time < t < next_main_time. In seguito lo scarto
	Event* last_event_regional = nullptr;
	Event* last_event_non_regional = nullptr;
	//int last_time = dynamic_cast<RegionalTrain*>(cur->GetTrain()) != nullptr ? next_local_arrive_time : next_main_arrive_time;
	for (auto i = cur + 1; i < events_.end() && (i->GetTime() + i->GetTrain()->getDelay()) <= next_main_arrive_time; i++)
	{
		//Se la prossima stazione è la stessa, il senso di percorrenza è lo stesso, il treno più veloce potrebbe subire ritardo, lo faccio partire prima di far partire il mio
		//Tengo in considerazione solo l'ultimo treno che parte.
		if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr)
		{
			if (i->GetStation() == next_main_station && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop && i->GetTrain() != cur->GetTrain())
			{
				last_event_non_regional = &(*i);
			}
		}
		else
		{
			if (i->GetStation() == next_local_station && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop && i->GetTrain() != cur->GetTrain())
			{
				last_event_regional = &(*i);
			}
		}
	}

	//Scarto il tempo se questo non è nel range che mi interessa
	if (last_event_regional != nullptr && last_event_regional->GetTime() + last_event_regional->GetTrain()->getDelay() > next_local_arrive_time)
		last_event_regional = nullptr;

	//A me interessa solo l'ultimo tra i 2 eventi (regionale e non regionale) che è capitato. Se ce ne sono più di uno.
	//Partendo dall'inizio degli eventi, appena ne trovo uno che è accaduto: quello è il meno recente => lo scarto.
	if (last_event_non_regional != nullptr && last_event_regional != nullptr)
	{
		for (auto i = events_.begin(); i < cur; i++)
		{
			//Se il treno non regionale è partito da questa stazione
			if (i->GetStation() == cur->GetStation() && last_event_non_regional->GetTrain() == i->GetTrain() && i->GetType() == EventType::TrainDeparture)
			{
				last_event_non_regional = nullptr;
				break;
			}
			//O se il treno non regionale è transitato per questa stazione
			else if (i->GetStation() == cur->GetStation() && last_event_non_regional->GetTrain() == i->GetTrain() && i->GetType() == EventType::PlatformRequest && dynamic_cast<localStation*>(i->GetStation()) != nullptr)
			{
				last_event_non_regional = nullptr;
				break;
			}
				
			//O se il treno regionale è partito da questa stazione
			else if (i->GetStation() == cur->GetStation() && last_event_non_regional->GetTrain() == i->GetTrain() && i->GetType() == EventType::TrainDeparture)
			{
				last_event_regional = nullptr;
				break;
			}
		}
	}

	//Tengo solo l'evento non nullo
	Event* last_event = last_event_non_regional == nullptr ? last_event_regional : last_event_non_regional;
	
	//Se un tale evento esiste devo posticipare la mia partenza
	if (last_event != nullptr)
	{
		const int minPerHour = 60;
		int next_time_arrive = last_event->GetTime() + last_event->GetTrain()->getDelay();
		int time_to_leave = static_cast<int>(static_cast<double>(distanceFromPark) / speedInStation * minPerHour);
		bool found = false;
		for (auto i = cur + 1; cur < events_.end() && next_time_arrive >= (i->GetTime() + i->GetTrain()->getDelay()) && !found; i++)		//Se si sono fermati alla stazione, allora adesso esiste già un evento di partenza dalla stazione
		{
			//Cerco l'ora a cui il treno davanti a me deve partire o transitare (se non regionale).
			if (cur->GetStation() == i->GetStation() && i->GetTrain() == last_event->GetTrain())
			{
				//Se per il treno che deve arrivare alla stazione dopo della mia è già definito un evento di partenza => si è già fermato alla stazione e sta aspettando, 
				//dovrà dunque partire dopo di me
				if (i->GetType() == EventType::TrainDeparture)
				{
					int arrive_time = last_event->GetTime();
					int speed_outside_station = getAverageSpeed(*(cur->GetStation()), *next_main_station, i->GetTime(), arrive_time, last_event->GetTrain());
					//Devo aspettare che il treno faccia 5 chilometri lenti a 80km/h e poi altri 5 alla sua velocità di crociera
					departure_time = i->GetTime() + i->GetTrain()->getDelay() + time_to_leave + static_cast<int>(round(static_cast<double>(kMinDistanceBetweenTrains) - distanceFromPark) / speed_outside_station * minPerHour);
					found = true;
				}
				//Altrimenti se il treno non è regionale ed esiste già un evento di richiesta del binario, aspetto che il treno (che sarà più prioritario di quello corrente), passi
				else if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr && i->GetType() == EventType::PlatformRequest)
				{
					const int safe_delay = 3;	//Prima di far partire il treno aspetto per 3 minuti che il treno davanti a me si sia distanziato di più di 10 chilometri
					int speed_outside_station = i->GetTrain()->getSpeed();
					const int wait_kilometers = 30; //quando il treno fa la richiesta deve fare 20km per arrivare alla stazione e poi devo aspettare 10km per far partire il treno dopo per mantenere la distanza tra i 2
					departure_time = i->GetTime() + i->GetTrain()->getDelay() + static_cast<int>(round(static_cast<double>(wait_kilometers) / speed_outside_station * minPerHour)) + safe_delay;
					found = true;
				}
			}
		}
	}
	return departure_time;
}


Station* Controller::GetNextStation(Station* current_station, Train* tr)
{
	Station* next_station;
	for (int i = 0; i < stations_.size(); i++)
	{
		const int x = tr->startFromOrigin ? i : stations_.size() - 1 - i;
		if (stations_[x] == current_station)
		{
			next_station = tr->startFromOrigin ? stations_[x + 1] : stations_[x - 1];
			return next_station;
		}
	}
}



//Trovo la stazione precedente nel senso di marcia                                                POTREBBE ESSERE UTILE A QUALCUNO
			/*Station* previous_station;
			for (int i = 0; i < stations_.size(); i++)
			{
				const int x = e.GetTrain()->startFromOrigin ? i : stations_.size() - 1 - i;
				if (stations_[x] == cur->GetStation())
				{
					previous_station = e.GetTrain()->startFromOrigin ? stations_[x - 1] : stations_[x + 1];
				}
			}*/

			/*
						//Calcolo la velocità che il treno in transito dovrebbe avere al passaggio per la stazione. Se il treno ora fosse su un'altra tratta, potrebbe avere velocità diversa.
										//Per farlo mi trovo la stazione principale precedente:
			Station* previous_station = nullptr;
			bool found = false;
			for (auto i = this_train_it; i >= this_train_events.begin() && !found; i--)
			{
				if (dynamic_cast<mainStation*>(i->GetStation()) != nullptr)
				{
					previous_station = i->GetStation();
					found = true;
				}
			}
			//Ora cerco l'orario di partenza del treno interessato dalla stazione precedente
			vector<Event> affected_train_events = GetEventsRelatedTo(last_affected_train);
			int previous_time_affected_train = 0;
			for (auto i = affected_train_events.begin(); i < affected_train_events.end(); i++)
			{
				if (i->GetStation() == previous_station && i->GetType() == EventType::TrainStop)
				{
					previous_time_affected_train = i->GetTime();
				}
			}

			int train_speed_between_stations = getAverageSpeed(*previous_station, *(cur->GetStation()), previous_time_affected_train, last_arrive_time, last_affected_train);
			*/


			/*vector<Event> this_train_events = GetEventsRelatedTo(cur->GetTrain());
					auto this_train_it = this_train_events.begin();
					//Posiziono cur_train all'interno della lista di eventi allo stesso livello di cur. Così facendo poi posso accedere alla stazione precedente e successiva nella tratta in modo molto più veloce
					for ( ; this_train_it < this_train_events.end(); this_train_it++)
					{
						if (this_train_it->GetTime() == cur->GetTime())
							break;
					}*/
					//Ora cur_train e cur puntano allo stesso evento ma in array diversi.
			/*
			if (dynamic_cast<localStation*>(cur->GetStation()) != nullptr)
			{
				//Gestisco gli eventi futuri generati da questo evento
				Station* next_station = nullptr;
				int next_arrive_time = -1;
				bool found = false;
				//Cerco l'orario di arrivo di questo treno alla stazione successiva
				for (auto i = this_train_it + 1; i < this_train_events.end(); i++)
				{
					if (dynamic_cast<mainStation*>(i->GetStation()) != nullptr)
					{
						next_arrive_time = i->GetTime();
						next_station = i->GetStation();
						found = true;
					}
				}

				//Controllo che non ci sia un treno più veloce che per arrivare alla prossima stazione deve rallentare per colpa del treno corrente
				Train* last_affected_train = nullptr;
				int last_arrive_time;	//Tempo di arrivo alla prossima stazione dell'ultimo treno che passa per la stazione corrente
				for (auto i = cur + 1; i < events_.end() && i->GetTime() < next_arrive_time; i++)
				{
					//Se la prossima stazione è la stessa, il treno è più prioritario di questo treno e il senso di percorrenza è lo stesso, il treno veloce potrebbe subire ritardo, lo faccio passare prima di far partire il mio
					//Tengo in considerazione solo l'ultimo treno che passa.
					if (i->GetStation() == next_station && dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop)
					{
						last_affected_train = i->GetTrain();
						last_arrive_time = i->GetTime();
					}
				}

				//Se un tale treno è presente, devo evitare che passi per la stazione dopo il treno che si è appena fermato è partito: lo rallenterebbe.
				if (last_affected_train != nullptr)
				{
					//Calcolo la velocità che il treno in transito dovrebbe avere al passaggio per la stazione.
					//Per farlo mi trovo la stazione principale precedente:
					Station* previous_station = nullptr;
					bool found = false;
					for (auto i = this_train_it; i >= this_train_events.begin() && !found; i--)
					{
						if (dynamic_cast<mainStation*>(i->GetStation()) != nullptr)
						{
							previous_station = i->GetStation();
							found = true;
						}
					}
					//Ora cerco l'orario di partenza del treno interessato dalla stazione precedente
					for (auto i = cur + 1; i < events_.end() && i->GetTime() <= last_arrive_time; i++)
					{
						if (i->GetTrain() == last_affected_train && i->GetStation() == cur->GetStation() && (i->GetTime() + last_affected_train->getDelay()) > cur->GetTime())	//Cerco l'evento di richiesta di un binario = passaggio del treno per quella stazione
							departure_time = i->GetTime() + 1;
					}
				}*/

				/*for (cur; cur < events_.end() && max_departure_time > cur->GetTime(); cur++)				                   TEMPO DI ATTESA FISSO
				{
					if (cur->GetStation() == e.GetStation() && dynamic_cast<RegionalTrain*>(cur->GetTrain()) == nullptr)
					{
						departure_time = cur->GetTime() + 1;
					}
				}
			}
			else      //Nel caso di stazione principale invece faccio partire prima quello più prioritario tra quelli già presenti
			{
				//Da gestire se sono arrivato a fine corsa  => non ho una stazione successiva (codice già scritto prima)


			}*/


			/*Train* last_affected_train = nullptr; //L'ultimo treno che passa per questa stazione che deve arrivare a destinazione prima di me
				int last_arrive_time;	//Tempo di arrivo alla prossima stazione dell'ultimo treno che passa per la stazione corrente
				for (auto i = cur + 1; i < events_.end() && (i->GetTime() + i->GetTrain()->getDelay()) < next_arrive_time; i++)
				{
					//Se la prossima stazione è la stessa, il senso di percorrenza è lo stesso, il treno più veloce potrebbe subire ritardo, lo faccio partire prima di far partire il mio
					//Tengo in considerazione solo l'ultimo treno che parte.
					if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr)
					{
						if (i->GetStation() == next_main_station && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop && i->GetTrain() != cur->GetTrain())
						{
							last_affected_train = i->GetTrain();
							last_arrive_time = i->GetTime();
						}
					}
					else
					{
						if (i->GetStation() == next_local_station && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop && i->GetTrain() != cur->GetTrain())
						{
							last_affected_train = i->GetTrain();
							last_arrive_time = i->GetTime();
						}
					}
				}

				if (last_affected_train != nullptr)
				{
					const int minPerHour = 60;

					int time_to_leave = distanceFromPark / speedInStation * minPerHour;	//Cambia perchè non ha double
					int delay_added = 0;
					bool found = false;
					for (auto i = cur + 1; cur < events_.end() && next_arrive_time > (i->GetTime() + i->GetTrain()->getDelay()) && !found; i++)		//Se si sono fermati alla stazione, allora adesso esiste già un evento di partenza dalla stazione
					{
						if (cur->GetStation() == i->GetStation() && i->GetTrain() == last_affected_train)
						{
							//Se per il treno che deve arrivare alla stazione dopo della mia è già definito un evento di partenza => si è già fermato alla stazione e sta aspettando,
							//dovrà dunque partire dopo di me
							if (i->GetType() == EventType::TrainDeparture)
							{
								int speed_outside_station = getAverageSpeed(*(cur->GetStation()), *next_main_station, i->GetTime(), last_arrive_time, last_affected_train);
								//Devo aspettare che il treno faccia 5 chilometri lenti a 80km/h e poi altri 5 alla sua velocità di crociera
								departure_time = i->GetTime() + time_to_leave + static_cast<int>((static_cast<double>(kMinDistanceBetweenTrains) - distanceFromPark) / speed_outside_station * minPerHour);
								found = true;
							}
							//Altrimenti se il treno non è regionale ed esiste già un evento di richiesta del binario, aspetto che il treno (che sarà più prioritario di quello corrente), passi
							else if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr && i->GetType() == EventType::PlatformRequest)
							{
								const int safe_delay = 3;	//Prima di far partire il treno aspetto per 3 minuti che il treno davanti a me si sia distanziato di più di 10 chilometri
								int speed_outside_station = i->GetTrain()->getSpeed();
								const int wait_kilometers = 30; //quando il treno fa la richiesta deve fare 20km per arrivare alla stazione e poi devo aspettare 10km per far partire il treno dopo per mantenere la distanza tra i 2
								departure_time = i->GetTime() + i->GetTrain()->getDelay() + static_cast<int>(static_cast<double>(wait_kilometers) / speed_outside_station * minPerHour) + safe_delay;
								found = true;
							}
						}
					}
				}
				return departure_time;*/