#include <iostream>
#include "./include/Car.h"
#include "include/CarController.h"

int main()
{
	Car car;
	CarController carController(car);

	std::string line;
	while (std::getline(std::cin, line))
	{
		if (!line.empty())
		{
			try
			{
				carController.HandleCommand(line);
			}
			catch (const std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			break;
		}
	}

	return 0;
}
