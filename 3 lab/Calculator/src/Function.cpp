#include "../include/Function.h"

void Function::SetValue(const std::vector<std::pair<std::string, std::string>>& tokens)
{
	/*m_value.SetExpression(expression);*/
	if (tokens.size() == 3)
	{
		m_value.operation = tokens.front().first;
		m_value.operands.assign(tokens.begin() + 1, tokens.end());
	}
	else
	{
		m_value.operands = tokens;
	}
}

std::string Function::GetName()
{
	return m_name;
}

Expression Function::GetExpression()
{
	return m_value;
}
