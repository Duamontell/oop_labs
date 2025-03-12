#pragma once

#include <stack>
#include <string>
#include <vector>

std::vector<std::string> ParseExpression(const std::string& line);
int EvaluateExpression(const std::vector<std::string>& expression);
// std::stack<char> CreateStackFromString(const std::string& line);
