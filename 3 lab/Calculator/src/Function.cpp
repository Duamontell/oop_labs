#include "../include/Function.h"

void Function::SetValue(const std::map<std::string, std::string> &expression)
{
	m_value.SetExpression(expression);
}

std::string Function::GetName()
{
	return m_name;
}

Expression Function::GetExpression()
{
	return m_value;
}
