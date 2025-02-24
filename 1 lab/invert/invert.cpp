// Лабораторная работа №1, задание №3, вариант №2 - Invert(80)

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

const int MATRIX_SIZE_3X3 = 3;
const int MATRIX_SIZE_2X2 = 2;

void FindElementPosition(double minor[MATRIX_SIZE_2X2][MATRIX_SIZE_2X2],
	double matrixT[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3], int pos, int row, int column)
{
	if (pos == 1)
	{
		minor[0][0] = matrixT[row][column];
	}
	else if (pos == 2)
	{
		minor[0][1] = matrixT[row][column];
	}
	else if (pos == 3)
	{
		minor[1][0] = matrixT[row][column];
	}
	else if (pos == 4)
	{
		minor[1][1] = matrixT[row][column];
	}
}

void SearchMinor(double minor[MATRIX_SIZE_2X2][MATRIX_SIZE_2X2],
	double matrixT[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3], int row, int column)
{
	int elementPos = 1;
	for (int i = 0; i < MATRIX_SIZE_3X3; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE_3X3; ++j)
		{
			if (i != row && j != column)
			{
				FindElementPosition(minor, matrixT, elementPos, i, j);
				elementPos++;
			}
		}
	}
}

double GetDeterminantMatrix2x2(double matrix[MATRIX_SIZE_2X2][MATRIX_SIZE_2X2])
{
	double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	return determinant;
}

double GetDeterminantMatrix3x3(double matrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3])
{
	double determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][2] * matrix[1][0] * matrix[2][1]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0] - matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2];
	return determinant;
}

void CheckDeterminant(double determinant)
{
	if (determinant == 0)
	{
		throw std::runtime_error("Non-invertible");
	}
}

double ChangeSign(double det, int row, int column)
{
	if (double parity = (row + column) % 2 == 0)
	{
		return det;
	}
	else
	{
		return -det;
	}
}

void GetInvertMatrix(double matrixT[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3],
	double invertedMatrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3])
{
	int count = 0;
	for (int i = 0; i < MATRIX_SIZE_3X3; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE_3X3; ++j)
		{
			double minor[MATRIX_SIZE_2X2][MATRIX_SIZE_2X2];
			SearchMinor(minor, matrixT, i, j);
			double det = GetDeterminantMatrix2x2(minor);
			det = ChangeSign(det, i, j);
			invertedMatrix[i][j] = det;
		}
	}
}

void GetTransposedMatrix(double matrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3],
	double matrixT[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3])
{
	for (int i = 0; i < MATRIX_SIZE_3X3; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE_3X3; ++j)
		{
			matrixT[i][j] = matrix[j][i];
		}
	}
}

void CountColumns(std::istream& inputFile)
{
	int count = 0;
	std::string str;
	std::getline(inputFile, str);
	std::istringstream iss(str);
	while (iss >> str)
	{
		count++;
	}

	if (count != MATRIX_SIZE_3X3)
	{
		throw std::runtime_error("Invalid matrix format");
	}

	inputFile.seekg(0);
}

// Возможно надо переделать и под stdin!
void GetMatrixFromFile(double matrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3], std::istream& input)
{
	std::string line;
	int rowCount = 0;
	double num1, num2, num3;
	CountColumns(input);

	while (std::getline(input, line))
	{
		if (rowCount >= MATRIX_SIZE_3X3)
		{
			throw std::runtime_error("Invalid matrix format");
		}

		// Возможно стоит сделать while (iss >> num)
		std::istringstream iss(line);
		if (iss >> num1 >> num2 >> num3)
		{
			matrix[rowCount][0] = num1;
			matrix[rowCount][1] = num2;
			matrix[rowCount][2] = num3;
		}
		else
		{
			throw std::runtime_error("Invalid matrix");
		}
		rowCount++;
	}

	if (rowCount != MATRIX_SIZE_3X3)
	{
		throw std::runtime_error("Invalid matrix format");
	}
}

std::ifstream GetInputFile(std::string fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open())
	{
		throw std::runtime_error("Input file not exists!");
	}
	return inputFile;
}

void PrintMatrix(double invertedMatrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3])
{
	for (int i = 0; i < MATRIX_SIZE_3X3; ++i)
	{
		for (int j = 0; j < MATRIX_SIZE_3X3; ++j)
		{
			std::cout << invertedMatrix[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

void ProcessFileMode(char* argv)
{
	std::ifstream inputFile = GetInputFile(argv);
	double matrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3];
	GetMatrixFromFile(matrix, inputFile);

	double determinant = GetDeterminantMatrix3x3(matrix);
	CheckDeterminant(determinant);

	double matrixT[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3];
	GetTransposedMatrix(matrix, matrixT);
	double invertedMatrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3];
	GetInvertMatrix(matrixT, invertedMatrix);

	PrintMatrix(invertedMatrix);
}

void ProcessStdinMode()
{
	double matrix[MATRIX_SIZE_3X3][MATRIX_SIZE_3X3];
	GetMatrixFromFile(matrix, std::cin);
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 2)
		{
			if (argv[1] == "-h")
			{
				std::cout << "Usage: <input.txt> or just run program without parameters" << std::endl;
			}
			else
			{
				ProcessFileMode(argv[1]);
			}
		}
		else if (argc == 1)
		{
			ProcessStdinMode();
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