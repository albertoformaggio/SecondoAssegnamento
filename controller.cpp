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
}

/* DA TESTAREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE, MANCA COSTRUTTORE STATION*/
void Controller::GetStations(string line_descr)
{
	ifstream lines_file;
	lines_file.open(line_descr);

	if (lines_file.fail())
	{
		cerr << "The file named: " << line_descr << "doesn't exist";
		//line_file.close(); Se lo lascio potrebbe lanciare eccezione,           DA TESTARE 
		throw FileNotFoundException();
	}

	//Gestisco la stazione di origine in modo "speciale", ha parametri diversi

	string station_name;
	lines_file >> station_name;
	int distance = 0;
	
	//Suppongo la prima stazione come principale, Ha distanza 0 dall'origine. Nel file � solo presente il nome
	stations_.push_back(new mainStation(station_name, distance));

	string line;
	while (!lines_file.eof())
	{
		//Da migliorare la lettura da input dei file, sto usando dei semplici indici 1,2,3,4 per le posizioni che non mi piacciono ==> regex
		getline(lines_file, line);
		distance = stoi(line.substr(line.size() - 1, 1));	//leggo l'ultimo numero della riga e lo converto in intero ===> � la distanza
		int station_type_number = stoi(line.substr(line.size() - 3, 1));
		station_name = line.substr(0, line.size() - 4);
		
		if (station_type_number == 0)
			stations_.push_back(new mainStation(station_name, distance));
		else
			stations_.push_back(new localStation(station_name, distance));
	}

	lines_file.close();
}

/* DA TESTAREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE, MANCA COSTRUTTORE STATION*/
void Controller::GetTimetable(string timetable)
{
	ifstream time_file;
	time_file.open(timetable);

	if (time_file.fail())
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
			cerr << "Il treno " << train_id << " non ha un orario di partenza: non pu� esistere";
		}
		else
		{
			trains_.push_back(tr);
			bool forward = first_station == 0;
			const int delay_time = 10;
			for (int i = 0; i < stations_.size(); i++)
			{
				Station* current_station = stations_[i];
				const int x = forward ? i : (stations_.size() - 1) - i;
				if (train_type != reg && dynamic_cast<localStation*>(current_station) != nullptr)		//COME FARE QUESTO CHECK?		Se il treno non � regionale e la stazione � locale, allora non ci sar� nessun evento di fermata del treno a tale stazione
				{
					int time;
					ss >> time;													//COMPLETARE CON I TEMPI NECESSARI SE MANCANTI
					if (ss.eofbit)
					{
						time = -1;
						Event* last = events_[events_.size() - 1];	//Ottengo l'ultimo evento di fermata inserito
						const Station* lastStation = last->GetStation();		//manca copy constructor/move constructor						
						tr->setSpeed(*lastStation, *current_station, last->GetTime(), time, delay_time);		//Creare un metodo nella classe TRAIN che date 2 distanze, un tempo di partenza, un tempo di arrivo e un tempo di ritardo ritorni la distanza. 
																																					//Se l'orario di partenza non � valido (cio� negativo), calcolarlo usando il minor tempo possibile pi� ritardo (magari il ritardo lo metti con parametro di default = 0)
					}
					
					Event* e = new TrainStop(time, tr, stations_[i]);
					events_.push_back(e);
				}
			}
		}
	}
	time_file.close();
}

void Controller::CheckValues()
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
		cur++;
		prev++;
	}
}

void Controller::EraseEventsRelatedTo(Station* st)
{
	for(auto it = events_.begin(); it != events_.end(); it++)
	{
		if((**it).GetStation() == st)
			it = events_.erase(it);
	}
}