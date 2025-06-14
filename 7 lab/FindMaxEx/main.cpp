#include <iostream>
#include <vector>

struct Sportsman
{
	std::string name;
	int height{};
	int weight{};
};

bool IsLessByHeight(Sportsman const& a, Sportsman const& b)
{
	return a.height < b.height;
}

bool IsLessByWeight(Sportsman const& a, Sportsman const& b)
{
	return a.weight < b.weight;
}

// Сделать строгую гарантию безопасности
// Посмотреть концепты
template < typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	T tempMaxValue = arr.front();
	for (const auto& element : arr)
	{
		if (!less(element, tempMaxValue))
		{
			tempMaxValue = element;
		}
	}

	maxValue = tempMaxValue;
	return true;
}

int main()
{
	std::vector<Sportsman> sportsmans = {
		{"Иван Иванов",    178,  72},
		{"Пётр Петров",    190,  85},
		{"Сергей Сергеев", 182,  77},
		{"Алексей Алексеев",201,  90},
		{"Дмитрий Дмитриев",167,  65},
		{"Николай Николаев",175,  80},
		{"Владимир Владимиров",188,  95},
		{"Михаил Михайлов",165,  60},
		{"Андрей Андреев",  193, 100},
		{"Евгений Евгеньев",180,  83}
	};
	Sportsman sportsmanWithMaxHeight;
	bool foundHeight = FindMaxEx(sportsmans, sportsmanWithMaxHeight, IsLessByHeight);
	if (foundHeight)
	{
		std::cout << "Sportsman with max height: "
			<< sportsmanWithMaxHeight.name << " "
			<< sportsmanWithMaxHeight.height << std::endl;
	}

	Sportsman sportsmanWithMaxWeight;
	bool foundWeight = FindMaxEx(sportsmans, sportsmanWithMaxWeight, IsLessByWeight);
	if (foundWeight)
	{
		std::cout << "Sportsman with max weight: "
		<< sportsmanWithMaxWeight.name << " "
		<< sportsmanWithMaxWeight.weight << std::endl;
	}

	return 0;
}
