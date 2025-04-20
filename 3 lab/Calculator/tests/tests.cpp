#include <gtest/gtest.h>
#include "Calculator.h"
#include "CalculatorController.h"

TEST(CalculatorTest, VarDeclareTest)
{
	Calculator calc;
	calc.VarDeclare("x");
	EXPECT_THROW(calc.VarDeclare("x"), std::invalid_argument);
	EXPECT_NO_THROW(calc.VarDeclare("y"));
}

TEST(CalculatorTest, VarAssignVarTest)
{
	Calculator calc;
	calc.VarDeclare("x");
	calc.VarAssign("y", "24");
	calc.VarAssign("x", "y");
	EXPECT_EQ(calc.GetValue("x"), 24.0);

	calc.VarDeclare("z");
	calc.VarAssign("x", "z");
	EXPECT_TRUE(std::isnan(calc.GetValue("x")));

	calc.VarAssign("x", "y");
	calc.VarAssign("y", "x");
	EXPECT_EQ(calc.GetValue("y"), 24.0);
}

TEST(CalculatorTest, PrintVarsTest)
{
	Calculator calc;
	calc.VarDeclare("y");
	calc.VarAssign("y", "5.4567");
	calc.VarDeclare("a");
	calc.VarAssign("a", "3.14159");

	testing::internal::CaptureStdout();
	calc.PrintVars();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("a:3.14"), std::string::npos);
	EXPECT_NE(output.find("y:5.46"), std::string::npos);
}

TEST(CalculatorTest, FunctionDeclareIdentifierTest)
{
	Calculator calc;
	calc.VarDeclare("abc");
	calc.VarAssign("abc", "3.14159");
	calc.FunctionDeclareIdentifier("aq", "abc");
	EXPECT_EQ(calc.GetValue("aq"), 3.14159 );

	calc.VarAssign("abc", "5");
	EXPECT_EQ(calc.GetValue("aq"), 5);

	calc.FunctionDeclareIdentifier("F", "aq");
	EXPECT_EQ(calc.GetValue("F"), 5);

	EXPECT_THROW(calc.FunctionDeclareIdentifier("aq", "F"), std::invalid_argument);
}

TEST(CalculatorTest, FunctionDeclareOperationTest)
{
	Calculator calc;
	calc.VarDeclare("x");
	calc.VarAssign("x", "3.14");
	calc.VarDeclare("y");
	calc.VarAssign("y", "4");
	calc.FunctionDeclareOperation("aq", {"x", "+", "y"});
	EXPECT_NEAR(calc.GetValue("aq"), 7.14, 0.001);

	calc.VarDeclare("z");
	calc.VarAssign("z", "15");
	calc.FunctionDeclareOperation("abc", {"aq", "*", "z"});
	EXPECT_NEAR(calc.GetValue("abc"), 107.1, 0.001);

	calc.VarAssign("x", "10");
	EXPECT_EQ(calc.GetValue("abc"), 210);

	EXPECT_THROW(calc.FunctionDeclareOperation("aq", {"abc", "-", "x"}),
		std::invalid_argument);
}

TEST(CalculatorTest, PrintIdentifierTest)
{
	Calculator calc;
	calc.VarDeclare("x");
	calc.VarAssign("x", "3.14");
	calc.FunctionDeclareIdentifier("A", "x");
	calc.FunctionDeclareOperation("B", {"x", "+", "A"});

	testing::internal::CaptureStdout();
	calc.PrintIdentifier("B");
	calc.PrintIdentifier("A");
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("6.28"), std::string::npos);
	EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST(CalculatorTest, PrintFunctionTest)
{
	Calculator calc;
	calc.VarDeclare("x");
	calc.VarAssign("x", "3.14");
	calc.FunctionDeclareIdentifier("A", "x");
	calc.FunctionDeclareOperation("B", {"x", "+", "A"});
	calc.FunctionDeclareOperation("z", {"B", "/", "A"});
	calc.FunctionDeclareOperation("gwen", {"z", "-", "z"});

	testing::internal::CaptureStdout();
	calc.PrintFunctions();
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("z:2"), std::string::npos);
	EXPECT_NE(output.find("A:3.14"), std::string::npos);
	EXPECT_NE(output.find("B:6.28"), std::string::npos);
	EXPECT_NE(output.find("gwen:0"), std::string::npos);
}

TEST(CalculatorControllerTest, VarCommandTest)
{
	Calculator calc;
	CalculatorController controller(calc);
	EXPECT_THROW(controller.HandleCommand("var"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("var "), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("var abc s"), std::invalid_argument);
}

TEST(CalculatorControllerTest, LetCommandTest)
{
	Calculator calc;
	CalculatorController controller(calc);
	EXPECT_THROW(controller.HandleCommand("let"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("let a "), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("let a s"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("let c s=5"), std::invalid_argument);
	EXPECT_NO_THROW(controller.HandleCommand("let a =5"));
	EXPECT_NO_THROW(controller.HandleCommand("let b=5"));
}

TEST(CalculatorControllerTest, FunctionCommandTest)
{
	Calculator calc;
	CalculatorController controller(calc);
	EXPECT_THROW(controller.HandleCommand("fn"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn s"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn s ="), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn s =="), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn abc=5*"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn abc=*"), std::invalid_argument);
	EXPECT_THROW(controller.HandleCommand("fn abc=5*5 55"), std::invalid_argument);

	calc.VarDeclare("x");
	calc.VarDeclare("y");
	EXPECT_NO_THROW(controller.HandleCommand("fn abc = x + y"));
	EXPECT_NO_THROW(controller.HandleCommand("fn a1c = x"));
	EXPECT_NO_THROW(controller.HandleCommand("fn a23 = y/a1c"));
	EXPECT_NO_THROW(controller.HandleCommand("fn sd2 = y  /a23"));
}

TEST(CalculatorTest, FibonacciTest)
{
	Calculator calc;
	CalculatorController controller(calc);

	calc.VarAssign("v0", "0");
	calc.VarAssign("v1", "1");
	calc.FunctionDeclareIdentifier("fib0", "v0");
	calc.FunctionDeclareIdentifier("fib1", "v1");
	calc.FunctionDeclareOperation("fib2", {"fib1", "+", "fib0"});
	calc.FunctionDeclareOperation("fib3", {"fib2", "+", "fib1"});
	calc.FunctionDeclareOperation("fib4", {"fib3", "+", "fib2"});
	calc.FunctionDeclareOperation("fib5", {"fib4", "+", "fib3"});
	calc.FunctionDeclareOperation("fib6", {"fib5", "+", "fib4"});
	calc.FunctionDeclareOperation("fib7", {"fib6", "+", "fib5"});
	calc.FunctionDeclareOperation("fib8", {"fib7", "+", "fib6"});
	calc.FunctionDeclareOperation("fib9", {"fib8", "+", "fib7"});
	calc.FunctionDeclareOperation("fib10", {"fib9", "+", "fib8"});
	calc.FunctionDeclareOperation("fib11", {"fib10", "+", "fib9"});
	calc.FunctionDeclareOperation("fib12", {"fib11", "+", "fib10"});
	calc.FunctionDeclareOperation("fib13", {"fib12", "+", "fib11"});
	calc.FunctionDeclareOperation("fib14", {"fib13", "+", "fib12"});
	calc.FunctionDeclareOperation("fib15", {"fib14", "+", "fib13"});
	calc.FunctionDeclareOperation("fib16", {"fib15", "+", "fib14"});
	calc.FunctionDeclareOperation("fib17", {"fib16", "+", "fib15"});
	calc.FunctionDeclareOperation("fib18", {"fib17", "+", "fib16"});
	calc.FunctionDeclareOperation("fib19", {"fib18", "+", "fib17"});
	calc.FunctionDeclareOperation("fib20", {"fib19", "+", "fib18"});
	calc.FunctionDeclareOperation("fib21", {"fib20", "+", "fib19"});
	calc.FunctionDeclareOperation("fib22", {"fib21", "+", "fib20"});
	calc.FunctionDeclareOperation("fib23", {"fib22", "+", "fib21"});
	calc.FunctionDeclareOperation("fib24", {"fib23", "+", "fib22"});
	calc.FunctionDeclareOperation("fib25", {"fib24", "+", "fib23"});
	calc.FunctionDeclareOperation("fib26", {"fib25", "+", "fib24"});
	calc.FunctionDeclareOperation("fib27", {"fib26", "+", "fib25"});
	calc.FunctionDeclareOperation("fib28", {"fib27", "+", "fib26"});
	calc.FunctionDeclareOperation("fib29", {"fib28", "+", "fib27"});
	calc.FunctionDeclareOperation("fib30", {"fib29", "+", "fib28"});
	calc.FunctionDeclareOperation("fib31", {"fib30", "+", "fib29"});
	calc.FunctionDeclareOperation("fib32", {"fib31", "+", "fib30"});
	calc.FunctionDeclareOperation("fib33", {"fib32", "+", "fib31"});
	calc.FunctionDeclareOperation("fib34", {"fib33", "+", "fib32"});
	calc.FunctionDeclareOperation("fib35", {"fib34", "+", "fib33"});
	calc.FunctionDeclareOperation("fib36", {"fib35", "+", "fib34"});
	calc.FunctionDeclareOperation("fib37", {"fib36", "+", "fib35"});
	calc.FunctionDeclareOperation("fib38", {"fib37", "+", "fib36"});
	calc.FunctionDeclareOperation("fib39", {"fib38", "+", "fib37"});
	calc.FunctionDeclareOperation("fib40", {"fib39", "+", "fib38"});
	calc.FunctionDeclareOperation("fib41", {"fib40", "+", "fib39"});
	calc.FunctionDeclareOperation("fib42", {"fib41", "+", "fib40"});
	calc.FunctionDeclareOperation("fib43", {"fib42", "+", "fib41"});
	calc.FunctionDeclareOperation("fib44", {"fib43", "+", "fib42"});
	calc.FunctionDeclareOperation("fib45", {"fib44", "+", "fib43"});
	calc.FunctionDeclareOperation("fib46", {"fib45", "+", "fib44"});
	calc.FunctionDeclareOperation("fib47", {"fib46", "+", "fib45"});
	calc.FunctionDeclareOperation("fib48", {"fib47", "+", "fib46"});
	calc.FunctionDeclareOperation("fib49", {"fib48", "+", "fib47"});
	calc.FunctionDeclareOperation("fib50", {"fib49", "+", "fib48"});
	/*std::cout << "Value fib50 = " << calc.GetValue("fib50") << std::endl;*/
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
