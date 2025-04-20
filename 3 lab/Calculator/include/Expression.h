#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <vector>

class Expression
{
public:
	void SetExpression(const std::vector<std::pair<std::string, std::string>>& tokens);

	[[nodiscard]] std::vector<std::pair<std::string, std::string>> GetOperands() const;
	[[nodiscard]] std::string GetOperation() const;
private:
	std::string m_operation;
	std::vector<std::pair<std::string, std::string>> m_operands;
};


#endif //EXPRESSION_H
