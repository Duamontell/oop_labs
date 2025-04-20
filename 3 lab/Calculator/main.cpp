#include <iostream>
#include "Calculator.h"
#include "CalculatorController.h"

int main()
{
	Calculator calc;
	CalculatorController controller(calc);

	std::string input;
	while (std::getline(std::cin, input))
	{
		if (!input.empty())
		{
			try
			{
				controller.HandleCommand(input);
			}
			catch (std::exception &e)
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
