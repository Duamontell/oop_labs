#pragma once
#include <iostream>
#include <vector>

std::vector<double> ReadNumbers(std::istream& input);
void MultiplyNumbersByMinElement(std::vector<double>& numbers);
void SortNumbers(std::vector<double>& numbers);
// ������ �� �����. ����� GetMinimalElement � NumbersMultiplyByScalar � ���������� ��� ��� �����
void PrintNumbers(std::vector<double>& numbers);
