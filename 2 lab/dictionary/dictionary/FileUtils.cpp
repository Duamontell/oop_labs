#include "FileUtils.h"
#include "Dictionary.h"

std::ifstream GetInputFile(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		return {};
	}
	return inputFile;
}

std::ofstream GetOutputFile(const std::string& fileName)
{
	std::ofstream outputFile(fileName);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open file");
	}
	return outputFile;
}