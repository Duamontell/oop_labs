#include "../include/Expression.h"
#include <iostream>

void Expression::SetExpression(const std::vector<std::pair<std::string, std::string>>& tokens)
{
	if (tokens.size() == 3)
	{
		m_operation = tokens.front().first;
		m_operands.assign(tokens.begin() + 1, tokens.end());
	}
	else
	{
		m_operands = tokens;
	}
}

std::vector<std::pair<std::string, std::string>> Expression::GetOperands() const
{
	return m_operands;
}

std::string Expression::GetOperation() const
{
	return m_operation;
}
