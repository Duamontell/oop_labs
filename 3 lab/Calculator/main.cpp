#include <iostream>
#include "Calculator.h"

int main()
{
	// Нужно сделать let <идентификатор1> = <идентификатор2>.
	Calculator calc;
	calc.VarDeclare("y");
	calc.VarAssign("y", 5.4567);
	calc.VarDeclare("a");
	calc.VarAssign("a", 3.14159);
	calc.PrintVars();

	return 0;
}
