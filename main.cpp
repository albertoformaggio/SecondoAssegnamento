#include "controller.h"
#include <iostream>
int main()
{
	Controller c("line_description.txt","timetables.txt");
	//c.printEvents();
	int speed = 240;
	int distance = 15;			//distanza richiesta-parcheggio
	int time = static_cast<int>(round(static_cast<double>(distance) / speed * 60));
	std::cout << time;
}
