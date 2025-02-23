// Лабораторная №1, задание №2, вариант №6

#include <iostream>
#include <limits>
#include <string>

std::string IntToString(int n, int radix)
{
	if (n == 0)
	{
		return "0";
	}

	std::string result;

	while (n != 0)
	{
		int mod = n % radix;
		n = n / radix;
		std::string digit;

		if (mod >= 0 && mod <= 9)
		{
			digit = char(mod) + '0';
		}
		else
		{
			digit = char(mod) + 'A' - 10;
		}

		result = result.insert(0, digit);
	}

	return result;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	int result = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		int digit = 0;
		char ch = str[i];
		if (ch >= '0' && ch <= '9')
		{
			digit = ch - '0';
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			digit = ch - 'A' + 10;
		}
		else
		{
			wasError = true;
			return 0;
		}

		if (digit >= radix)
		{
			wasError = true;
			return 0;
		}

		if (result <= (std::numeric_limits<int>::max() - digit) / radix)
		{
			result = result * radix + digit;
		}
		else
		{
			wasError = true;
			return 0;
		}
	}

	return result;
}

void CheckNumberMinus(std::string& number, bool& IsNumberMinus)
{
	if (number[0] == '-')
	{
		IsNumberMinus = true;
		number = number.substr(1);
	}
}

bool CheckRadixs(int radixInit, int radixEnd)
{
	if ((radixInit >= 2 && radixInit <= 36) && (radixEnd >= 2 && radixEnd <= 36))
	{
		return false;
	}

	return true;
}

void CheckError(bool& wasError)
{
	if (wasError)
	{
		throw std::runtime_error("Invalid input data!");
	}
}

void PrintResult(std::string numberInNewRadix, bool IsNumberMinus)
{
	if (IsNumberMinus)
	{
		numberInNewRadix = numberInNewRadix.insert(0, "-");
	}

	std::cout << numberInNewRadix << std::endl;
}

void ProcessStream(char* argv[])
{
	std::string initialRadix(argv[1]), finalRadix(argv[2]), number(argv[3]);
	bool wasError = false;
	bool IsNumberMinus = false;
	int radixInit = StringToInt(initialRadix, 10, wasError);
	int radixEnd = StringToInt(finalRadix, 10, wasError);
	wasError = CheckRadixs(radixInit, radixEnd);

	CheckNumberMinus(number, IsNumberMinus);
	int numberInTen = StringToInt(number, radixInit, wasError);

	CheckError(wasError);
	std::string numberInNewRadix = IntToString(numberInTen, radixEnd);
	PrintResult(numberInNewRadix, IsNumberMinus);
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 4)
		{
			ProcessStream(argv);
		}
		else
		{
			throw std::runtime_error("Wrong number of arguments!");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
