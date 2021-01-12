#include "controller.h"
#include <iostream>

int main()
{
	Controller c("line_description.txt","timetables_2.txt");
	c.printEvents();
}
