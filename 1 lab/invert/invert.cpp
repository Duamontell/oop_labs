// Лабораторная работа №1, задание №3, вариант №2 - Invert(80)
#include <exception>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

double ReadNumber(char ch, std::ifstream& inputFile)
{
		bool point = false;
		std::string number;
		number.push_back(ch);
		while (inputFile.get(ch)) {
				if (isdigit(ch)) {
						number.push_back(ch);
				}
				else if (!point && ch == '.') {
						number.push_back(ch);
						point = true;
				}
				else {
						inputFile.unget();
						break;
				}
		}

		return std::stod(number);
}

void GetMatrixFromFile(double matrix[3][3], std::ifstream& inputFile)
{
		char ch;
		std::string line;
		bool numberStarted = false;
		int rowCount = 0, columntCout = 0, precision = 0;
		while (inputFile.get(ch)) {
				if (isdigit(ch) || "-") {
						numberStarted = true;
						double number = ReadNumber(ch, inputFile);
						matrix[rowCount][columntCout] = number;
						columntCout++;
				}
				else if (ch == '\n') {
						rowCount++;
						columntCout = 0;
				}
				else {
						throw std::runtime_error("Invalid matrix");
				}
				/*if (ch == '\t')
				{
					columntCout++;
				}*/

				if (rowCount > 3 || columntCout > 3) {
						throw std::runtime_error("Invalid matrix format");
				}
		}

		if (rowCount == 0) {
				throw std::runtime_error("Invalid matrix format");
		}
}

std::ifstream GetInputFile(std::string fileName)
{
		std::ifstream inputFile(fileName);
		if (!inputFile.is_open()) {
				throw std::runtime_error("Input file not exists!");
		}
		return inputFile;
}

void ProcessFileMode(char* argv)
{
		std::ifstream inputFile = GetInputFile(argv);
		double matrix[3][3];
		GetMatrixFromFile(matrix, inputFile);
}

int main(int argc, char* argv[])
{
		std::string num = "1.2340000";
		try {
				if (argc == 2) {
						if (argv[1] == "-h") {
								std::cout << "Usage: <input.txt> or just run program without parameters" << std::endl;
						}
						else {
								ProcessFileMode(argv[1]);
						}
				}
				else if (argc == 1) {
						// ProcessStdinMode();
				}
				else {
						throw std::runtime_error("Wrong number of arguments!");
				}
		}
		catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
				return 1;
		}

		return 0;
}