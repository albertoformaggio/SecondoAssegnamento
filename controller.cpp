/*!
	@author Formaggio Alberto
*/
#include "controller.h"
#include <iostream>

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
	
	//Suppongo la prima stazione come principale, Ha distanza 0 dall'origine. Nel file è solo presente il nome
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
		//Quando il ciclo è terminato, in tmp è presente la prima cifra della riga, ovvero il tipo di stazione 
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
		Train* tr;
		switch (train_type)
		{
		case reg:
			tr = new RegionalTrain(train_id);				//Devo inserirci un riferimento con &
			break;
		case hs:
			tr = new HSTrain(train_id);
			break;
		case hs_super:
			tr = new HSTrainSuper(train_id);
			
			break;
		}

		if (ss.eof()) //Se il file non ha nemmeno l'orario di partenza, ignoro il treno passato
		{
			cerr << "Il treno " << train_id << " non ha un orario di partenza: non può esistere";
		}
		else
		{
			trains_.push_back(tr);
			bool forward = first_station == 0;
			const int delay_time = 10;
			for (int i = 0; i < stations_.size(); i++)
			{
				const int x = forward ? i : (stations_.size() - 1) - i;
				Station* current_station = stations_.at(i);				
				if (train_type == reg || (train_type != reg && dynamic_cast<localStation*>(current_station) == nullptr))		//COME FARE QUESTO CHECK?		Se il treno non è regionale e la stazione è locale, allora non ci sarà nessun evento di fermata del treno a tale stazione
				{
					int time;
					if (!(ss >> time))
					{
						time = -1;
						Event* last = events_.at(events_.size() - 1);	//Ottengo l'ultimo evento di fermata inserito
						const Station* lastStation = last->GetStation();		//manca copy constructor/move constructor						
						tr->setAverageSpeed(*lastStation, *current_station, last->GetTime(), time, delay_time);		//Creare un metodo nella classe TRAIN che date 2 distanze, un tempo di partenza, un tempo di arrivo e un tempo di ritardo ritorni la distanza. 
																																					//Se l'orario di partenza non è valido (cioè negativo), calcolarlo usando il minor tempo possibile più ritardo (magari il ritardo lo metti con parametro di default = 0)
					}
					
					Event* e = new TrainStop(time, tr, stations_.at(i));
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
	while(cur != stations_.end())
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
	while(it < events_.end())
	{
		if ((**it).GetStation() == st)
			it = events_.erase(it);
		else
			it++;
	}
}

void Controller::printEvents()
{
	for (int i = 0; i < events_.size(); i++)
	{
		cout << events_[i]->GetStation()->st_name << " " << events_[i]->GetTrain()->identifying_number << " " << events_[i]->GetTime() << endl;
	}
}

void Controller::CheckTimetable()
{

}
