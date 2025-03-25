#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Variable.h"
#include <map>

class Calculator
{
public:
	void VarDeclare(const std::string& varName);
	void VarAssign(const std::string& varName, double value);

	Variable* GetVar(const std::string& varName);
	void PrintVars() const;
private:
	std::map<std::string, Variable> m_variables;
};


#endif // CALCULATOR_H
