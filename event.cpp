/*!
	@author Formaggio Alberto
*/

#include "event.h"

using namespace std;

void Event::SetTime(int time)
{
	if (time < 0)
		throw invalid_argument("Time cannot be negative");
	time_ = time;
}