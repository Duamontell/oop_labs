#include <gtest/gtest.h>
#include "Calculator.h"

TEST(CalculatorTest, VarDeclarations)
{
	Calculator calc;
	calc.VarDeclare("x");
	Variable *var = calc.GetVar("x");
	EXPECT_EQ(var->GetName(), "x");
}

TEST(CalculatorTest, VarAssignNumber)
{
	Calculator calc;
	calc.VarDeclare("y");
	calc.VarAssign("y", 5.4567);
	Variable *var = calc.GetVar("y");
	EXPECT_EQ(var->GetValue(), 5.4567);
}

TEST(CalculatorTest, VarAssignVar) {}

TEST(CalculatorTest, PrintVars)
{
	Calculator calc;
	calc.VarDeclare("y");
	calc.VarAssign("y", 5.4567);
	calc.VarDeclare("a");
	calc.VarAssign("a", 3.14159);

	// ДОДЕЛАТЬ
	std::vector<std::string> input = {
		"EngineOn",
		"SetGear 1",
		"SetSpeed SS"
	};
	calc.PrintVars();
}

TEST(CalculatorTest, FunctionDeclareIdentifier)
{
	Calculator calc;
	/*calc.FunctionDeclare("aq")*/
}

TEST(CalculatorTest, FunctionDeclareOperation) {}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
