#include "Calculator.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include "Constants.h"

void Calculator::VarDeclare(const std::string &newVarName)
{
	if (m_variables.find(newVarName) != m_variables.end() || m_functions.find(newVarName) != m_functions.end())
	{
		throw std::invalid_argument("Name already exists");
	}
	m_variables.emplace(newVarName, Variable(newVarName));
}

void Calculator::EditArrayCalculatedFunctions(const std::string &identifier)
{
	std::vector<std::string> keysToRemove;
	for (auto it = m_fuctionsValues.begin(); it != m_fuctionsValues.end(); ++it)
	{
		const auto& operands = GetFunction(it->first)->GetExpression().operands;
		for (auto operand : operands)
		{
			if (operand.first == identifier)
			{
				keysToRemove.emplace_back(it->first);
				break;
			}
		}
	}

	for (auto key : keysToRemove)
	{
		m_fuctionsValues.erase(key);
		EditArrayCalculatedFunctions(key);
	}
}

void Calculator::VarAssign(const std::string& varName, const std::string& value)
{
	if (m_variables.find(varName) == m_variables.end() && m_functions.find(varName) == m_functions.end())
	{
		VarDeclare(varName);
	}
	// Из блока catch брать логику и добавить возможность переменной присваивать функцию

	try
	{
		double number = std::stod(value);
		GetVar(varName)->SetValue(number);
	}
	catch (const std::exception&)
	{
		GetVar(varName)->SetValue(GetVar(value)->GetValue());
	}

	EditArrayCalculatedFunctions(varName);

}

Variable *Calculator::GetVar(const std::string &varName)
{
	auto it = m_variables.find(varName);
	if (it != m_variables.end())
	{
		return &it->second;
	}
	throw std::invalid_argument("Name does not exist");
}

Function *Calculator::GetFunction(const std::string &fnName)
{
	auto it = m_functions.find(fnName);
	if (it != m_functions.end())
	{
		return &it->second;
	}
	throw std::invalid_argument("Name does not exist");
}

// Проверить, нужна ли эта функция = НЕ НУЖНА
/*double Calculator::GetOperandValue(const std::string &identifier)
{
	if (IsVar(identifier))
	{
		Variable *var = GetVar(identifier);
		return var->GetValue();
	}
	return GetValue(identifier);
}*/

double Calculator::GetValue(const std::string &identifier)
{
	if (IsVar(identifier))
	{
		return GetVar(identifier)->GetValue();
	}
	if (m_fuctionsValues.find(identifier) != m_fuctionsValues.end())
	{
		return m_fuctionsValues[identifier];
	}

	std::vector<std::pair<std::string, std::string>> operands = GetFunction(identifier)->GetExpression().operands;

	if (operands.size() == 1)
	{
		auto it = operands.begin();
		std::string newIdentifier = it->first;
		std::string type = it->second;

		if (type == WORD_VARIABLE)
		{
			Variable *var = GetVar(newIdentifier);
			if (!IsVar(identifier))
			{
				m_fuctionsValues.emplace(identifier, var->GetValue());
			}
			return var->GetValue();
		}
		if (type == WORD_FUNCTION)
		{
			Function *fn = GetFunction(newIdentifier);
			return GetValue(fn->GetName());
		}
	}

	if (operands.size() == 2)
	{
		auto it = operands.begin();
		double leftValue = GetValue(it->first);
		++it;
		double rightValue = GetValue(it->first);

		std::string operation = GetFunction(identifier)->GetExpression().operation;
		if (operation == OPERATION_PLUS)
		{
			m_fuctionsValues.insert({identifier, leftValue + rightValue});
			return leftValue + rightValue;
		}
		if (operation == OPERATION_MINUS)
		{
			m_fuctionsValues.insert({identifier, leftValue - rightValue});
			return leftValue - rightValue;
		}
		if (operation == OPERATION_MULTIPLY)
		{
			m_fuctionsValues.insert({identifier, leftValue * rightValue});
			return leftValue * rightValue;
		}
		if (operation == OPERATION_DIVIDE)
		{
			if (rightValue == 0)
			{
				m_fuctionsValues.insert({identifier, NAN});
				return NAN;
			}
			m_fuctionsValues.insert({identifier, leftValue / rightValue});
			return leftValue / rightValue;
		}
	}
	throw std::invalid_argument("Name does not exist");
}

bool Calculator::IsVar(const std::string &identifier)
{
	// Добавить метод, который возвращает опциональное значение
	try
	{
		GetVar(identifier);
		return true;
	}
	catch (...)
	{
		GetFunction(identifier);
		return false;
	}
}

void Calculator::FunctionDeclareIdentifier(const std::string &fnName, const std::string &identifierName)
{
	if (m_functions.find(fnName) != m_functions.end() || m_variables.find(fnName) != m_variables.end())
	{
		throw std::invalid_argument("Name already exists");
	}
	m_functions.emplace(fnName, Function(fnName));
	std::vector<std::pair<std::string, std::string>> expression = {};
	if (!IsVar(identifierName))
	{
		expression = {{identifierName, WORD_FUNCTION}};
	}
	else
	{
		expression = {{identifierName, WORD_VARIABLE}};
	}
	GetFunction(fnName)->SetValue(expression);
}

void Calculator::FunctionDeclareOperation(const std::string &fnName, const std::vector<std::string> &tokens)
{
	if (m_functions.find(fnName) != m_functions.end() || m_variables.find(fnName) != m_variables.end())
	{
		throw std::invalid_argument("Name already exists");
	}
	std::vector<std::pair<std::string, std::string>> expression = {{tokens[1], "operation"}};
	expression.emplace_back(tokens[0], IsVar(tokens[0]) ? WORD_VARIABLE : WORD_FUNCTION);
	expression.emplace_back(tokens[2], IsVar(tokens[2]) ? WORD_VARIABLE : WORD_FUNCTION);
	m_functions.emplace(fnName, Function(fnName));
	GetFunction(fnName)->SetValue(expression);
}

void Calculator::PrintIdentifier(const std::string &identifierName)
{
	if (m_variables.find(identifierName) != m_variables.end()
		|| m_functions.find(identifierName) != m_functions.end())
	{
		std::cout << std::setprecision(3) << GetValue(identifierName) << std::endl;
	}
	else
	{
		throw std::invalid_argument("Name does not exist");
	}
}

void Calculator::PrintVars()
{
	for (const auto &[name, var]: m_variables)
	{
		std::cout << std::setprecision(3) << name << OUTPUT_DELIMETER << var.GetValue() << "\n";
	}
}

void Calculator::PrintFunctions()
{
	for (auto &[name, function]: m_functions)
	{
		std::cout << std::setprecision(3) << name << OUTPUT_DELIMETER << GetValue(name) << "\n";
	}
}
