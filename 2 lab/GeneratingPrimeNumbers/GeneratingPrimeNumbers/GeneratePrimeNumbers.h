#pragma once

#include <set>
#include <string>

int ParseInputNumber(std::string input);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintPrimeNumbers(const std::set<int>& primeNumbers);