#include "Calculator.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>

void Calculator::VarDeclare(const std::string &varName)
{
	m_variables.emplace(varName, Variable(varName));
}

void Calculator::VarAssign(const std::string &varName, double value)
{
	GetVar(varName)->SetValue(value);
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

void Calculator::PrintVars() const
{
	for (const auto &[name, var]: m_variables)
	{
		std::cout << std::setprecision(3) << name << ":" << var.GetValue() << "\n";
	}
}
