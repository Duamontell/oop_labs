#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../vector/Vector.h"

// Добавить тесты для ProcessNumbers
SCENARIO("Reading numbers from input")
{
	WHEN("vector valid input")
	{
		std::istringstream iss("23 58    3  -2.0  36.126342");
		THEN("function return vector")
		{
			std::vector<double> result = ReadNumbers(iss);
			REQUIRE(result == std::vector<double>{ 23, 58, 3, -2.0, 36.126342 });
		}
	}
	WHEN("input contains invalid characters")
	{
		std::istringstream iss("4 3d -2.0  3.142");
		THEN("we will catch the error")
		{
			REQUIRE_THROWS_AS(ReadNumbers(iss), std::runtime_error);
		}
	}
	WHEN("input is empty")
	{
		std::istringstream iss("");
		THEN("function return empty array")
		{
			std::vector<double> result = ReadNumbers(iss);
			REQUIRE(result == std::vector<double>{});
		}
	}
}

SCENARIO("SortNumbers sorting array")
{
	WHEN("SortNumbers get an array")
	{
		std::vector<double> numbers = { 3.22, 1.5, 4.8, 2.0, 3.22 };
		SortNumbers(numbers);
		THEN("function must returns sorted array")
		{
			std::vector<double> expected = { 1.5, 2.0, 3.22, 3.22, 4.8 };
			REQUIRE(numbers == expected);
		}
	}
	WHEN("SortNumbers get an empty array")
	{
		std::vector<double> numbers = {};
		SortNumbers(numbers);
		THEN("function must returns sorted array")
		{
			std::vector<double> expected = {};
			REQUIRE(numbers == expected);
		}
	}
	WHEN("") {}
}
