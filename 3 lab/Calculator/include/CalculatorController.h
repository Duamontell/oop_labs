#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H
#include "Calculator.h"

enum class CalculatorCommand
{
	Var,
	Let,
	Function,
	Print,
	PrintVars,
	PrintFunctions,
	UnknownCommand,
};

class CalculatorController
{
public:
	explicit CalculatorController(Calculator& calc) : m_calc(calc) {}

	void HandleCommand(const std::string& command);

private:
	Calculator& m_calc;

	CalculatorCommand ParseCommand(const std::string & cmd);
	bool IsValideName(const std::string & string);
	void HandleLetCommand(std::istringstream & iss);
	void HandleFunctionCommand(std::istringstream & iss);
};



#endif //CALCULATORCONTROLLER_H
