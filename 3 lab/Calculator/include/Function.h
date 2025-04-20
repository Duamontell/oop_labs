#ifndef FUNCTION_H
#define FUNCTION_H
/*#include "Expression.h"*/
#include <string>
#include <vector>

struct Expression
{
	std::string operation;
	std::vector<std::pair<std::string, std::string>> operands;
};

class Function
{
public:
	explicit Function(const std::string &fnName) : m_name(fnName) {}
	void SetValue(const std::vector<std::pair<std::string, std::string>> &expression);

	std::string GetName();
	Expression GetExpression();
private:
	std::string m_name;
	Expression m_value;
};


#endif //FUNCTION_H
