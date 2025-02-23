#include <fstream>
#include <iostream>
#include <string>

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (true)
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos == std::string::npos)
		{
			result.append(subject, pos);
			break;
		}
		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	bool textExists = false;
	while (std::getline(input, line))
	{
		if (input.fail() && !input.eof())
		{
			throw std::runtime_error("ERROR");
		}
		textExists = true;
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}

	if (!textExists)
	{
		std::cout << "ERROR" << std::endl;
	}
}

void ProcessFileMode(char* argv[])
{
	std::ifstream inputFile;
	OpenInputFile(inputFile, argv[1]);
	std::ofstream outputFile;
	OpenOutputFile(outputFile, argv[2]);

	CopyStreamWithReplacement(inputFile, outputFile, argv[3], argv[4]);
	outputFile.flush();
}

void ProcessConsoleMode()
{
	std::string search, replace;
	std::getline(std::cin, search);
	std::getline(std::cin, replace);

	CopyStreamWithReplacement(std::cin, std::cout, search, replace);
}

void OpenInputFile(std::ifstream& inputFile, std::string fileName)
{
	inputFile.open(fileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("ERROR");
	}

	return;
}

void OpenOutputFile(std::ofstream& outputFile, std::string fileName)
{
	outputFile.open(fileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("ERROR");
	}

	return;
}

void PrintUsage()
{
	std::cout << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 5)
		{
			ProcessFileMode(argv);
		}
		else if (argc == 1)
		{
			ProcessConsoleMode();
		}
		else if (argc == 2 && std::string(argv[2]) == "-h")
		{
			PrintUsage();
			return 0;
		}
		else
		{
			throw std::runtime_error("ERROR");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}

// Создать функцию OpenFile
// RVO и NRVO
// Выделить отдельную функцию - парс аргументов
// В мейне проверяем на правильность парса, вызываем конкретные функции по копированию и реплейсу