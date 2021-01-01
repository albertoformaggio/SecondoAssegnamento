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

	//Suppongo la prima stazione come principale, Ha distanza 0 dall'origine. Nel file è solo presente il nome
	stations_.push_back(MainStation(station_name, distance));

	string line;
	while (!lines_file.eof())
	{
		//Da migliorare la lettura da input dei file, sto usando dei semplici indici 1,2,3,4 per le posizioni che non mi piacciono ==> regex
		getline(lines_file, line);
		distance = stoi(line.substr(line.size() - 1, 1));	//leggo l'ultimo numero della riga e lo converto in intero ===> è la distanza
		int station_type_number = stoi(line.substr(line.size() - 3, 1));
		station_name = line.substr(0, line.size() - 4);
		
		if (station_type_number == 0)
			stations_.push_back(MainStation(station_name, distance));
		else
			stations_.push_back(LocalStation(station_name, distance));
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
	while (!time_file.eof())
	{
		string line;
		getline(time_file, line);
		istringstream ss(line);

		ss >> train_id >> first_station >> train_type;
		Train tr;
		switch (train_type)
		{
		case 0:
			tr = RegionalTrain(train_id);
			trains_.push_back(tr);
			break;
		case 1:
			tr = HSTrain(train_id);
			trains_.push_back(tr);
			break;
		case 2:
			tr = HSTrainSuper(train_id);
			trains_.push_back(tr);
			break;
		}
		
		bool forward = first_station == 0;
		for (int i = 0; i < stations_.size(); i++)
		{	
			const int x = forward ? i : (stations_.size()-1) - i;
			if (!(tr.getType() != "Regional" && stations_[i].getType() == "Local"))		//COME FARE QUESTO CHECK?		Se il treno non è regionale e la stazione è locale, allora non ci sarà nessun evento di fermata del treno a tale stazione
			{
				int time;
				ss >> time;
				Event e(EventType::kTrainStop, time, tr, stations_[i]);
				events_.push_back(e);
			}
		}	
	}

	time_file.close();
}