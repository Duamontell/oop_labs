#include <gtest/gtest.h>
#include "Calculator.h"

TEST(CalculatorTest, VarAssignVar)
{
	Calculator calc;
	calc.VarDeclare("x", "");
	calc.VarAssign("y", "24");
	calc.VarAssign("x", "y");
	EXPECT_EQ(calc.GetValue("x"), 24.0);
}

TEST(CalculatorTest, PrintVars)
{
	Calculator calc;
	calc.VarDeclare("y","");
	calc.VarAssign("y", "5.4567");
	calc.VarDeclare("a", "");
	calc.VarAssign("a", "3.14159");

	// ДОДЕЛАТЬ
	std::vector<std::string> input = {"EngineOn", "SetGear 1", "SetSpeed SS"};
	calc.PrintVars();
}

TEST(CalculatorTest, FunctionDeclareIdentifier)
{
	Calculator calc;
	calc.VarDeclare("abc", "");
	calc.VarAssign("abc", "3.14159");
	calc.FunctionDeclareIdentifier("aq", "abc");
	EXPECT_EQ(calc.GetValue("aq"), 3.14159 );

	calc.VarAssign("abc", "5");
	EXPECT_EQ(calc.GetValue("aq"), 5);

	calc.FunctionDeclareIdentifier("F", "aq");
	EXPECT_EQ(calc.GetValue("F"), 5);
}

TEST(CalculatorTest, FunctionDeclareOperation)
{
	Calculator calc;
	calc.VarDeclare("x", "");
	calc.VarAssign("x", "3.14");
	calc.VarDeclare("y", "");
	calc.VarAssign("y", "4");
	calc.FunctionDeclareOperation("aq", {"x", "+", "y"});
	EXPECT_NEAR(calc.GetValue("aq"), 7.14, 0.001);
	calc.VarDeclare("z", "");
	calc.VarAssign("z", "15");
	calc.FunctionDeclareOperation("abc", {"aq", "*", "z"});
	EXPECT_NEAR(calc.GetValue("abc"), 107.1, 0.001);
	calc.VarAssign("x", "10");
	EXPECT_EQ(calc.GetValue("abc"), 210);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
