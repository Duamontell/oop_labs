#pragma once
#include <iostream>
#include <vector>

std::vector<double> ReadNumbers(std::istream& input);
void MultiplyNumbersByMinElement(std::vector<double>& numbers);
void SortNumbers(std::vector<double>& numbers);
// Убрать из загол. файла GetMinimalElement и NumbersMultiplyByScalar и переделать под них тесты
void PrintNumbers(std::vector<double>& numbers);
