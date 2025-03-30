#include "Calculator.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <src/gtest-internal-inl.h>

void Calculator::VarDeclare(const std::string &newVarName, const std::string &varName)
{
	if (varName.empty())
	{
		m_variables.emplace(newVarName, Variable(newVarName));
	}
	else
	{
		m_variables.emplace(newVarName, Variable(newVarName));
		GetVar(newVarName)->SetValue(GetVar(varName)->GetValue());
	}
}

void Calculator::VarAssign(const std::string& varName, const std::string& value)
{
	if (m_variables.find(varName) != m_variables.end())
	{
		try
		{
			double number = std::stod(value);
			GetVar(varName)->SetValue(number);
		}
		catch (const std::exception&)
		{
			VarDeclare(varName, value);
		}
	}
	else
	{
		VarDeclare(varName, "");
		
	}
}

void Calculator::PrintVars() const
{
	for (const auto &[name, var]: m_variables)
	{
		std::cout << std::setprecision(3) << name << ":" << var.GetValue() << "\n";
	}
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

double Calculator::GetOperandValue(const std::string &identifier)
{
	if (IsVar(identifier))
	{
		Variable *var = GetVar(identifier);
		return var->GetValue();
	}
	return GetValue(identifier);
}


double Calculator::GetValue(const std::string &identifier)
{
	if (IsVar(identifier))
	{
		return GetVar(identifier)->GetValue();
	}

	std::map<std::string, std::string> operands = GetFunction(identifier)->GetExpression().GetOperands();

	if (operands.size() == 1)
	{
		auto it = operands.begin();
		std::string newIdentifier = it->first;
		std::string type = it->second;

		if (type == "variable")
		{
			Variable *var = GetVar(newIdentifier);
			return var->GetValue();
		}
		if (type == "function")
		{
			Function *fn = GetFunction(newIdentifier);
			return GetValue(fn->GetName());
		}
	}

	if (operands.size() == 2)
	{
		auto it = operands.begin();
		double leftValue = GetOperandValue(it->first);
		++it;
		double rightValue = GetOperandValue(it->first);

		std::string operation = GetFunction(identifier)->GetExpression().GetOperation();
		if (operation == "+") return leftValue + rightValue;
		if (operation == "-") return leftValue - rightValue;
		if (operation == "*") return leftValue * rightValue;
		if (operation == "/")
		{
			if (rightValue == 0)
			{
				return NAN;
			}
			return leftValue / rightValue;
		}
	}
	throw std::invalid_argument("Name does not exist");
}

bool Calculator::IsVar(const std::string &identifier)
{
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
	m_functions.emplace(fnName, Function(fnName));
	std::map<std::string, std::string> expression = {};
	if (!IsVar(identifierName))
	{
		expression = {{identifierName, "function"}};
	}
	else
	{
		expression = {{identifierName, "variable"}};
	}
	GetFunction(fnName)->SetValue(expression);
}

void Calculator::FunctionDeclareOperation(const std::string &fnName, const std::vector<std::string> &tokens)
{
	m_functions.emplace(fnName, Function(fnName));
	std::map<std::string, std::string> expression = {{tokens[1], "operation"}};
	if (!IsVar(tokens[0]))
	{
		expression.insert({tokens[0], "function"});
	}
	else
	{
		expression.insert({tokens[0], "variable"});
	}
	if (!IsVar(tokens[2]))
	{
		expression.insert({tokens[2], "function"});
	}
	else
	{
		expression.insert({tokens[2], "variable"});
	}
	GetFunction(fnName)->SetValue(expression);
}
