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

bool Event::operator < (const Event& other) const
{
	return time_ + train_->getDelay() < other.time_ + other.GetTrain()->getDelay();
}
