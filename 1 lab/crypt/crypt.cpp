// crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::ifstream GetInputFile(std::string fileName)
{
	std::ifstream inputFile(fileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Input file not exists!");
	}
	return inputFile;
}

std::ofstream GetOutputFile(std::string fileName)
{
	std::ofstream outputFile(fileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("Output file not exists!");
	}
	return outputFile;
}

int GetKey(std::string keyStr)
{
	int key;
	std::istringstream iss(keyStr);

	if (!(iss >> key) || !(iss.eof()) || key < 0 || key > 255)
	{
		throw std::runtime_error("Wrong key!");
	}

	return key;
}

char MixByte(char byte)
{
	char newbyte = 0;

	char bit = (byte >> 7) & 1;
	newbyte = (byte & ~(1 << 5)) | (bit << 5);

	/*bit = (byte >> 6) & 1;
	newbyte = (newbyte & ~(1 << 1)) | (bit << 1);

	bit = (byte >> 5) & 1;
	newbyte = (newbyte & ~1) | bit;*/

	bit = (byte >> 5) & 3;
	newbyte = (newbyte & ~3) | bit;

	bit = (byte >> 4) & 1;
	newbyte = (newbyte & ~(1 << 7)) | (bit << 7);

	bit = (byte >> 3) & 1;
	newbyte = (newbyte & ~(1 << 6)) | (bit << 6);

	bit = (byte >> 2) & 1;
	newbyte = (newbyte & ~(1 << 4)) | (bit << 4);

	bit = (byte >> 1) & 1;
	newbyte = (newbyte & ~(1 << 3)) | (bit << 3);

	bit = byte & 1;
	newbyte = (newbyte & ~(1 << 2)) | (bit << 2);

	return newbyte;
}

void ProcessCrypt(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	char byte;
	char newbyte = 0;
	while (inputFile.read(&byte, 1))
	{
		byte = byte ^ key;
		newbyte = MixByte(byte);

		outputFile.put(newbyte);
	}
}

char UnMixByte(const char byte)
{
	char newbyte = 0;

	char bit = (byte >> 5) & 1;
	newbyte = (byte & ~(1 << 7)) | (bit << 7);

	bit = (byte >> 1) & 1;
	newbyte = (newbyte & ~(1 << 6)) | (bit << 6);

	bit = byte & 1;
	newbyte = (newbyte & ~(1 << 5)) | (bit << 5);

	bit = (byte >> 7) & 1;
	newbyte = (newbyte & ~(1 << 4)) | (bit << 4);

	bit = (byte >> 6) & 1;
	newbyte = (newbyte & ~(1 << 3)) | (bit << 3);

	bit = (byte >> 4) & 1;
	newbyte = (newbyte & ~(1 << 2)) | (bit << 2);

	bit = (byte >> 3) & 1;
	newbyte = (newbyte & ~(1 << 1)) | (bit << 1);

	bit = (byte >> 2) & 1;
	newbyte = (newbyte & ~1) | bit;

	return newbyte;
}

void ProcessDecrypt(std::ifstream& inputFile, std::ofstream& outputFile, const int& key)
{
	char byte;
	char newbyte = 0;
	while (inputFile.read(&byte, 1))
	{
		newbyte = UnMixByte(byte);
		newbyte = newbyte ^ key;

		outputFile.put(newbyte);
	}
}

void ChooseMode(std::ifstream& inputFile, std::ofstream& outputFile,
	const int& key, const std::string& mode)
{
	if (mode == "crypt")
	{
		ProcessCrypt(inputFile, outputFile, key);
	}
	else if (mode == "decrypt")
	{
		ProcessDecrypt(inputFile, outputFile, key);
	}
}

void ProcessParseArg(char* argv[])
{
	std::ifstream inputFile = GetInputFile(argv[2]);
	std::ofstream outputFile = GetOutputFile(argv[3]);
	int key = GetKey(argv[4]);
	std::string mode(argv[1]);

	ChooseMode(inputFile, outputFile, key, mode);
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 5)
		{
			ProcessParseArg(argv);
		}
		else
		{
			throw std::runtime_error("Wrong number arguments!");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
