#include "controller.h"
#include <iostream>

int main()
{
	Controller c("line_description_1.txt","timetables_3.txt");
	c.printEvents();
}
