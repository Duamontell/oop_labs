#ifndef VARIABLE_H
#define VARIABLE_H
#include <cmath>
#include <string>

class Variable
{
public:
	explicit Variable(const std::string& var) : m_name(var) {}
	void SetValue(double value);

	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] double GetValue() const;
private:
	std::string m_name;
	double m_value = NAN;
};


#endif //VARIABLE_H
