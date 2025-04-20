#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "Variable.h"
#include "Function.h"
#include <map>
#include <unordered_map>
#include <vector>

class Calculator
{
public:
	void VarDeclare(const std::string &newVarName);
	void VarAssign(const std::string& varName, const std::string& value);
	void FunctionDeclareIdentifier(const std::string& fnName, const std::string& identifierName);
	void FunctionDeclareOperation (const std::string& fnName, const std::vector<std::string>& tokens);
	void PrintIdentifier(const std::string& identifierName);
	void PrintFunctions();
	void PrintVars();
	double GetValue(const std::string& identifier);

private:
	std::map<std::string, Variable> m_variables;
	std::map<std::string, Function> m_functions;
	std::unordered_map<std::string, double> m_fuctionsValues;

	Variable* GetVar(const std::string& varName);
	Function* GetFunction(const std::string& fnName);
	bool IsVar(const std::string &identifier);
	double GetOperandValue(const std::string &identifier);
	void EditArrayCalculatedFunctions(const std::string &identifier);
};


#endif // CALCULATOR_H
