#include "GeneratePrimeNumbers.h"
#include <chrono>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

const int MAX_INPUT_NUMBER = 100000000;

int ParseInputNumber(std::string input)
{
	int number;
	std::istringstream iss(input);

	if (!(iss >> number) || !(iss.eof()) || number > MAX_INPUT_NUMBER)
	{
		throw std::runtime_error("Wrong input number!");
	}

	return number;
}

std::vector<bool> FindPrimeNumbers(int n)
{
	int size = (n + 1) / 2;
	std::vector<bool> isPrime(size, true);
	isPrime[0] = false;

	for (int i = 1; (2 * i + 1) * (2 * i + 1) <= n; ++i)
	{
		if (isPrime[i])
		{
			int p = 2 * i + 1;
			for (int j = (p * p - 1) / 2; j < size; j += p)
			{
				isPrime[j] = false;
			}
		}
	}
	return isPrime;
	/*std::vector<bool> isPrime(n + 1, true);
	for (int i = 2; i * i <= n; ++i)
	{
		if (isPrime[i])
		{
			for (int j = i * i; j <= n; j += i)
			{
				isPrime[j] = false;
			}
		}
	}
	return isPrime;*/
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::set<int> primeNumbers;
	std::vector<bool> sieve = FindPrimeNumbers(upperBound);
	if (upperBound >= 2)
	{
		primeNumbers.insert(2);
	}
	for (int i = 1; i < sieve.size(); ++i)
	{
		if (sieve[i])
		{
			int num = 2 * i + 1;
			// std::cout << num << "\n";
			primeNumbers.insert(num);
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time spent: " << duration.count() << " ms\n";

	return primeNumbers;
}

void PrintPrimeNumbers(const std::set<int>& primeNumbers)
{
	std::ostringstream oss;
	for (int prime : primeNumbers)
	{
		oss << prime << "\n";
	}
	std::cout << oss.str();
}