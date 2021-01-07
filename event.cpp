/*!
	@author Formaggio Alberto
*/

#include "train.h"
#include "event.h"
#include "station.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void Event::SetTime(int time)
{
	if (time < 0)
		throw invalid_argument("Time cannot be negative");
	time_ = time;
}

void TrainStop::performAction()
{
	int hour = GetTime() / 60;
	int minute = GetTime() % 60;
	cout << "Il treno " << GetTrain()->identifying_number << " e' arrivato alla stazione " << GetStation()->st_name << " alle ore " << hour << ":" << minute << endl;
	cout << "con " << GetTrain()->getDelay() << " minuti di ritardo." << endl;
}