#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <map>
#include <string>

class Expression
{
public:
	void SetExpression(std::map<std::string, std::string> tokens);

	[[nodiscard]] std::map<std::string, std::string> GetOperands() const;
	[[nodiscard]] std::string GetOperation() const;
private:
	std::string m_operation;
	std::map<std::string, std::string> m_operands;
};


#endif //EXPRESSION_H
