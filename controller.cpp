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

/* DA TESTAREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE*/
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

	//Gestisco la stazione di origine in modo "speciale", ha parametri diversi

	string station_name;
	string line;
	getline(lines_file, line);
	istringstream ss(line);
	int distance = 0;
	ss >> station_name;

	//Suppongo la prima stazione come principale, Ha distanza 0 dall'origine. Nel file � solo presente il nome
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

	lines_file.close();
}

/* DA TESTAREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE, MANCA COSTRUTTORE STATION*/
void Controller::GetTimetable(string timetable)
{
	ifstream time_file;
	time_file.open(timetable);

	if (!time_file.is_open())
	{
		cerr << "The file named: " << timetable << "doesn't exist";
		//line_file.close(); Se lo lascio potrebbe lanciare eccezione,           DA TESTARE 
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
		Train* tr;
		switch (train_type)
		{
		case reg:
			tr = new RegionalTrain(train_id, from_origin);				//Devo inserirci un riferimento con &			//METTII A POSTO QUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
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
			cerr << "Il treno " << train_id << " non ha un orario di partenza: non pu� esistere";
		}
		else
		{
			trains_.push_back(tr);
			bool forward = first_station == 0;
			const int delay_time = 10;
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

					Event e(time, tr, stations_.at(x), EventType::TrainStop);
					events_.push_back(e);
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
	sort(events_.begin(), events_.begin());
	for (int i = 0; i < events_.size(); i++)
	{
		switch (events_[i].GetType())
		{
		case EventType::TrainStop: handleTrainStop(i);
			break;
		case EventType::TrainDeparture: cout << events_[i].GetTrain()->identifying_number << " " << events_[i].GetStation()->st_name << " " << events_[i].GetTime() << endl;
		}
	}
	/*for (cur; cur < end; cur++)
	{
		cout << cur->GetStation()->st_name << " " << cur->GetTrain()->identifying_number << " " << cur->GetTime();
	}*/
}

void Controller::CheckTimetable()
{
	for (int i = 0; i < trains_.size(); i++)
	{
		Train* tr = trains_.at(i);
		vector<Event> ev = GetEventsRelatedTo(tr);
		for (int j = 1; j < ev.size(); j++)
		{
			int arrive_time = ev.at(j).GetTime();			
			int leave_time = ev.at(j - 1).GetTime();
			Station* previous = ev.at(j - 1).GetStation();

			getAverageSpeed(*previous, *(ev.at(j).GetStation()), leave_time, arrive_time, tr);
			
			if (arrive_time != ev.at(j).GetTime())
			{
				int evaluated_delay = arrive_time - ev[j].GetTime();
				int k = j + 1;
				for (k; k < ev.size(); k++)
				{
					int cur_time = events_[k].GetTime();
					events_[k].SetTime(cur_time + evaluated_delay);
				}
				cout << "Orario di arrivo del treno " << tr->identifying_number << " alla stazione " << ev[j].GetStation()->st_name << " non compatibile" << endl;
				cout << "con la velocita' del treno. " << k - j << " orari cambiati di conseguenza" << endl;
			}
		}
	}
}

//Il ritardo del treno va aggiunto a TUTTI gli eventi successivi quando arrivo in parcheggio => solo i parcheggi mi fanno perdere tempo rispetto alla tabella di marcia

void Controller::handleTrainStop(int cur)
{
	//Stampo l'evento che e' appena accaduto
	int hour = events_[cur].GetTime() / 60;
	hour %= 24;
	int minute = events_[cur].GetTime() % 60;
	cout << "Il treno " << events_[cur].GetTrain()->identifying_number << " e' arrivato alla stazione " << events_[cur].GetStation()->st_name << " alle ore ";
	cout << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << minute << endl;
	cout << "con " << events_[cur].GetTrain()->getDelay() << " minuti di ritardo." << endl;

	//Prima controlla che non sia il capolinea del treno. Ottengo l'ultima stazione della tratta secondo il senso di marcia del treno
	Station* last_line_station = events_[cur].GetTrain()->startFromOrigin ? stations_[stations_.size() - 1] : stations_[0];
	if (last_line_station != events_[cur].GetStation())
	{
		int departure_time = min_wait + events_[cur].GetTime() + events_[cur].GetTrain()->getDelay();		
		Event departure(departure_time, events_[cur].GetTrain(), events_[cur].GetStation(), EventType::TrainDeparture);
		events_.push_back(departure);
		auto i = events_.begin();
		while(i < events_.end())
		{
			i++;
		}
		//Ordino sulla base di tempo + ritardo solamente gli eventi che devono ancora essere analizzati
		sort(i, events_.end());
	}
	else
	{
		cout << "Il treno " << events_[cur].GetTrain()->identifying_number << " e' arrivato alla fine della corsa con un ritardo di " << events_[cur].GetTrain()->getDelay() << " minuti" << endl;
	}
}

vector<Event> Controller::GetEventsRelatedTo(Train* tr)
{
	vector<Event> events;
	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].GetTrain() == tr) //Confronto gli indirizzi di memoria
			events.push_back(events_.at(i));
	}

	return events; //Costruttore di move di vector usato, non viene fatta l'intera copia
}


int Controller::CheckDeparture(vector<Event>::iterator cur)
{
	//Controlla di non essere ultima stazione della tratta

	int departure_time = min_wait + cur->GetTime();
	Station* next_station = nullptr;
	int next_arrive_time = -1;
	bool found = false;
	//Cerco l'orario di arrivo di questo treno alla stazione successiva
	for (auto i = cur + 1; i < events_.end() && !found; i++)
	{
		if (i->GetTrain() == cur->GetTrain() && dynamic_cast<mainStation*>(i->GetStation()) != nullptr)
		{
			next_arrive_time = i->GetTime();
			next_station = i->GetStation();
			found = true;
		}
	}

	vector<Train*> affected_trains; //Tutti i treni con cui il mio treno interagisce: potrebbero essersi fermati oppure no
	vector<int> arrive_times;	//Tempo di arrivo alla prossima stazione dell'ultimo treno che passa per la stazione corrente
	for (auto i = cur + 1; i < events_.end() && i->GetTime() < next_arrive_time; i++)
	{
		//Se la prossima stazione è la stessa, il senso di percorrenza è lo stesso, il treno più veloce potrebbe subire ritardo, lo faccio partire prima di far partire il mio
		//Tengo in considerazione solo l'ultimo treno che parte.
		if (i->GetStation() == next_station && i->GetTrain()->startFromOrigin == cur->GetTrain()->startFromOrigin && i->GetType() == EventType::TrainStop)
		{
			affected_trains.push_back(i->GetTrain());
			arrive_times.push_back(i->GetTime());
		}
	}

	if (!affected_trains.empty())
	{
		const int minPerHour = 60;

		int time_to_leave = distanceFromPark / speedInStation * minPerHour;
		int delay_added = 0;
		for (int j = 0; j < affected_trains.size(); j++)
		{
			for (auto i = cur + 1; cur < events_.end() && next_arrive_time > i->GetTime(); i++)		//Se si sono fermati alla stazione, allora adesso esiste già un evento di partenza dalla stazione
			{
				if (cur->GetStation() == i->GetStation() && i->GetTrain() == affected_trains.at(j))
				{
					if (i->GetType() == EventType::TrainDeparture)
					{
						int speed_outside_station = getAverageSpeed(*(cur->GetStation()), *next_station, i->GetTime(), arrive_times.at(j), affected_trains.at(j));
						//Devo aspettare che il treno faccia 5 chilometri lenti e poi altri 5 alla sua velocità di crociera
						departure_time = i->GetTime() + time_to_leave + static_cast<int>((static_cast<double>(kMinDistanceBetweenTrains) - distanceFromPark) / speed_outside_station * minPerHour);
						delay_added = departure_time - i->GetTime() + time_to_leave;
					}
					else if (dynamic_cast<RegionalTrain*>(i->GetTrain()) == nullptr && i->GetType() == EventType::PlatformRequest)
					{
						const int safe_delay = 5;
						int speed_outside_station = i->GetTrain()->getSpeed();
						const int wait_kilometers = 30; //quando il treno fa la richiesta deve fare 20km per arrivare alla stazione e poi devo aspettare 10km per far partire il treno dopo
						departure_time = i->GetTime() + i->GetTrain()->getDelay() + static_cast<int>(static_cast<double>(wait_kilometers) / speed_outside_station * minPerHour) + safe_delay;
					}
				}
			}
		}
	}
	return departure_time;
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