#include "ExpressionUtils.h"
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>

const char OPEN_BRACKET = '(';
const char CLOSE_BRACKET = ')';
const char PLUS = '+';
const char MULTIPLY = '*';

void CheckBracket(char ch, bool& bracketWasOpen)
{
		if (ch == OPEN_BRACKET)
		{
				bracketWasOpen = true;
		}
		else if (ch == CLOSE_BRACKET)
		{
				bracketWasOpen = false;
		}
}

void CheckOperation(char ch, bool& wasOperation)
{
		if ((ch == PLUS || ch == MULTIPLY))
		{
				if (!wasOperation)
				{
						wasOperation = true;
				}
				else
				{
						throw std::runtime_error("ERROR");
				}
		}
}

std::string SpacesFilterExpression(const std::string& input)
{
		return std::regex_replace(input, std::regex(" "), "");
}

std::vector<std::string> ParseExpression(const std::string& expr)
{
		const char MINUS = '-';

		std::vector<std::string> tokens;
		std::string token;
		bool bracketWasOpen = false;
		bool wasOperation = true;

		std::string filteredExpr = SpacesFilterExpression(expr);
		std::regex wrongComb(R"(\(\d|\(\(+|(?:\+|\*)\)|\(\))");
		if (std::regex_search(filteredExpr, wrongComb))
		{
				throw std::invalid_argument("ERROR");
		}

		for (size_t i = 0; i < filteredExpr.size(); ++i)
		{
				//char ch = filteredExpr[i];
				std::string ch;
				ch += filteredExpr[i];

				if (ch == OPEN_BRACKET || ch == CLOSE_BRACKET || ch == PLUS || ch == MULTIPLY)
				{
						CheckBracket(ch, bracketWasOpen);
						//CheckOperation(ch, wasOperation);
						tokens.push_back(std::string(1, ch));
				}
				else if ((std::isdigit(ch) || (ch == MINUS && i + 1 < filteredExpr.size() && std::isdigit(filteredExpr[i + 1])))
						&& bracketWasOpen && wasOperation)
				{
						token.clear();
						token += ch;

						while (i + 1 < filteredExpr.size() && std::isdigit(filteredExpr[i + 1]))
						{
								token += filteredExpr[++i];
						}

						tokens.push_back(token);
				}
				else
				{
						throw std::runtime_error("ERROR");
				}
		}

		if (bracketWasOpen)
		{
				throw std::runtime_error("ERROR");
		}

		return tokens;
}

int EvaluateExpression(const std::vector<std::string>& expression)
{
		std::stack<std::string> stack;
		for (size_t i = 0; i < expression.size(); ++i)
		{
				std::string element = expression[i];
				/*if (element || element == MULTIPLY)
				{

				}*/
		}
		/*if (!stack.empty())
		{
				throw std::runtime_error("ERROR");
		}*/
		return 0;
}

// std::stack<char> CreateStackFromString(const std::string& expression)
//{
//	std::stack<char> stack;
//	for (char ch : expression)
//	{
//		stack.push(ch);
//	}
//	return stack;
// }