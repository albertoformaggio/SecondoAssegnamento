#include "controller.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Controller c("line_description_1.txt","timetables_1.txt");
	c.printEvents();
}
