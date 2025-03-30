#include "../include/Expression.h"
#include <iostream>

void Expression::SetExpression(std::map<std::string, std::string> tokens)
{
	if (tokens.size() == 3)
	{
		m_operation = tokens.begin()->first;
		m_operands.insert(std::next(tokens.begin()), tokens.end());
	}
	else
	{
		m_operands.insert(tokens.begin(), tokens.end());
	}
}

std::map<std::string, std::string> Expression::GetOperands() const
{
	return m_operands;
}

std::string Expression::GetOperation() const
{
	return m_operation;
}
