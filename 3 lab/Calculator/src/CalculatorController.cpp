#include "../include/CalculatorController.h"
#include "Constants.h"
#include <algorithm>
#include <io.h>
#include <iostream>
#include <sstream>

std::string StringTrim(const std::string &line)
{
	auto start = std::find_if(line.begin(), line.end(),
		[](unsigned char ch)
	{
		return !std::isspace(ch);
	});
	if (start == line.end())
	{
		return "";
	}

	auto end = std::find_if(line.rbegin(), line.rend(),
		[](unsigned char ch)
	{
		return !std::isspace(ch);
	}).base();

	return std::string(start, end);
}

void CalculatorController::HandleCommand(const std::string &input)
{
	std::istringstream iss(input);
	std::string command, argument;
	iss >> command;

	switch (ParseCommand(command))
	{
		case CalculatorCommand::Var:
			iss >> argument;
			IsValideName(argument) && iss.eof()
				? m_calc.VarDeclare(argument)
				: throw std::invalid_argument("Invalid usage");
			break;
		case CalculatorCommand::Let:
			HandleLetCommand(iss);
			break;
		case CalculatorCommand::Function:
			HandleFunctionCommand(iss);
			break;
		case CalculatorCommand::Print:
			iss >> argument;
			(!argument.empty()) && iss.eof()
				? m_calc.PrintIdentifier(argument)
				: throw std::invalid_argument("Invalid usage");
			break;
		case CalculatorCommand::PrintVars:
			m_calc.PrintVars();
			break;
		case CalculatorCommand::PrintFunctions:
			m_calc.PrintFunctions();
			break;
		case CalculatorCommand::UnknownCommand:
			throw std::invalid_argument("Unknown command");
	}
}

CalculatorCommand CalculatorController::ParseCommand(const std::string &command)
{
	if (command == "var") return CalculatorCommand::Var;
	if (command == "let") return CalculatorCommand::Let;
	if (command == "fn") return CalculatorCommand::Function;
	if (command == "print") return CalculatorCommand::Print;
	if (command == "printvars") return CalculatorCommand::PrintVars;
	if (command == "printfns") return CalculatorCommand::PrintFunctions;
	return CalculatorCommand::UnknownCommand;
}

bool CalculatorController::IsValideName(const std::string &string)
{
	if (std::isdigit(string[0]) || string.empty())
	{
		return false;
	}
	for (auto ch: string)
	{
		if (!std::isalnum(ch) && ch != '_')
		{
			return false;
		}
	}

	return true;
}

void CalculatorController::HandleLetCommand(std::istringstream &iss)
{
	std::string assignment;
	std::getline(iss >> std::ws, assignment);
	std::istringstream tokenStream(assignment);

	std::string varName, varValue;
	std::getline(tokenStream, varName, OPERATION_EQUAL);
	std::getline(tokenStream, varValue, OPERATION_EQUAL);
	varName = StringTrim(varName);
	varValue = StringTrim(varValue);
	IsValideName(varName) && (!varValue.empty()) && varName != varValue
		? m_calc.VarAssign(varName, varValue)
		: throw std::invalid_argument("Invalid usage");
}

void CalculatorController::HandleFunctionCommand(std::istringstream &iss)
{
	std::string assignment;
	std::getline(iss >> std::ws, assignment);
	std::istringstream tokenStream(assignment);

	std::string functionName, functionValue;
	std::getline(tokenStream, functionName, OPERATION_EQUAL);
	std::getline(tokenStream, functionValue, OPERATION_EQUAL);
	functionName = StringTrim(functionName);
	functionValue = StringTrim(functionValue);

	std::vector<std::string> expression;
	std::string token;
	for ( auto ch: functionValue)
	{
		if (ch == OPERATION_PLUS[0]
			|| ch == OPERATION_MINUS[0]
			|| ch == OPERATION_MULTIPLY[0]
			|| ch == OPERATION_DIVIDE[0])
		{
			if (!token.empty())
			{
				expression.push_back(token);
				token.clear();
			}
			expression.emplace_back(1, ch);
		}
		else if (!std::isspace(ch))
		{
			token += ch;
		}
		else
		{
			if (token.empty())
			{
				continue;
			}
			expression.push_back(token);
			token.clear();
		}
	}
	if (!token.empty())
	{
		expression.push_back(token);
	}

	if (expression.size() == 3 && IsValideName(expression[0]) && IsValideName(expression[2]))
	{
		m_calc.FunctionDeclareOperation(functionName, expression);
	}
	else if (expression.size() == 1 && IsValideName(expression[0])
			&& (expression[0] != OPERATION_PLUS
			&& expression[0] != OPERATION_MINUS
			&& expression[0] != OPERATION_MULTIPLY
			&& expression[0] != OPERATION_DIVIDE))
	{
		m_calc.FunctionDeclareIdentifier(functionName, expression[0]);
	}
	else
	{
		throw std::invalid_argument("Invalid usage");
	}
}
