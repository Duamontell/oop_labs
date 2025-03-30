#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Variable.h"
#include "Function.h"
#include <map>
#include <vector>

class Calculator
{
public:
	void VarDeclare(const std::string& newVarName, const std::string &varName);
	void VarAssign(const std::string& varName, const std::string& value);
	void PrintVars() const;
	void FunctionDeclareIdentifier(const std::string& fnName, const std::string& varName);
	void FunctionDeclareOperation (const std::string& fnName, const std::vector<std::string>& tokens);

	double GetValue(const std::string& identifier);

private:
	std::map<std::string, Variable> m_variables;
	std::map<std::string, Function> m_functions;

	Variable* GetVar(const std::string& varName);
	Function* GetFunction(const std::string& fnName);
	bool IsVar(const std::string &identifier);
	double GetOperandValue(const std::string &identifier);
};


#endif // CALCULATOR_H
