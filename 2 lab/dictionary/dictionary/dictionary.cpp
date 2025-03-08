#include "Dictionary.h"
#include "ConsoleUtils.h"
#include "FileUtils.h"

int main(int argc, char* argv[])
{
	SetConsoleSettings();
	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Wrong numbers parameters!");
		}

		std::multimap<std::string, std::string> dictionaryEngRus;
		std::multimap<std::string, std::string> dictionaryRusEng;
		std::ifstream dictionaryFile = GetInputFile(argv[1]);

		ImportDictionary(dictionaryEngRus, dictionaryRusEng, dictionaryFile);
		RunUserDialog(dictionaryEngRus, dictionaryRusEng, argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}