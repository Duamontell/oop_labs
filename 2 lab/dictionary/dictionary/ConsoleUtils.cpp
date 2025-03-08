#include "ConsoleUtils.h";

#include <Windows.h>
#include <clocale>

void SetConsoleSettings()
{
	setlocale(LC_ALL, "Ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}