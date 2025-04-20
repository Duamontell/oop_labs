#include <iostream>
#include "include/CDate.h"

int main()
{
	try
	{
		CDate date(1, Month::JANUARY, 1972);
		int day = date.GetDay();
		std::cout << "Hello, World!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
