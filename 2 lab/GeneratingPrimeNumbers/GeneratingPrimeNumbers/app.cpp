#include "GeneratePrimeNumbers.h"
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Wrong number");
		}

		int upperBound = ParseInputNumber(argv[1]);
		std::set<int> primeNumbers;
		primeNumbers = GeneratePrimeNumbersSet(upperBound);
		std::cout << "Cout numbers: " << primeNumbers.size() << "\n";
		// PrintPrimeNumbers(primeNumbers);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}