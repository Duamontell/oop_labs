#include "ExpressionUtils.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			std::vector<std::string> expression = ParseExpression(line);
			int result = EvaluateExpression(expression);
			std::cout << result << "\n";
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return 0;
		}
	}

	return 0;
}