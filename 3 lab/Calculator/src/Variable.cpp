#include "../include/Variable.h"

void Variable::SetValue(double value)
{
	m_value = value;
}

std::string Variable::GetName() const
{
	return m_name;
}

double Variable::GetValue() const
{
	return m_value;
}
