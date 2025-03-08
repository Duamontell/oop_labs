// Лабораторная работа №2, задание №1, вариант №2 - vector (20)

#include "Vector.h"

int main()
{
	try
	{
		std::vector<double> numbers = ReadNumbers(std::cin);
		MultiplyNumbersByMinElement(numbers);
		SortNumbers(numbers);
		PrintNumbers(numbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}