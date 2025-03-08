#include "Vector.h"

#include <algorithm>
#include <iomanip>
#include <iterator>

#include <sstream>

std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers = {};
	double num;
	while (input >> num)
	{
		numbers.push_back(num);
	}
	if (input.fail() && !input.eof())
	{
		throw std::runtime_error("ERROR");
	}

	return numbers;
}

double GetMinimalElement(const std::vector<double>& numbers)
{
	auto minNum = std::min_element(numbers.begin(), numbers.end());
	if (minNum != numbers.end())
	{
		return *minNum;
	}

	return 0.0;
}

void NumbersMultiplyByScalar(std::vector<double>& numbers, double scalar)
{
	std::transform(numbers.begin(), numbers.end(), numbers.begin(),
		[scalar](double num) { return num * scalar; });
}

void SortNumbers(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}

void MultiplyNumbersByMinElement(std::vector<double>& numbers)
{
	double minNum = GetMinimalElement(numbers);
	NumbersMultiplyByScalar(numbers, minNum);
}

void PrintNumbers(std::vector<double>& numbers)
{
	std::cout << std::fixed << std::setprecision(3);
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<double>(std::cout, " "));
	std::cout << '\n';
}