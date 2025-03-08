#pragma once

#include <fstream>

std::ifstream GetInputFile(const std::string& fileName);
std::ofstream GetOutputFile(const std::string& fileName);