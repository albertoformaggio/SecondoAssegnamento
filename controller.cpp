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
			MainStation st(station_name, distance);
		else
			LocalStation st(station_name, distance);

		stations_.push_back(st);
	}

	lines_file.close();
}