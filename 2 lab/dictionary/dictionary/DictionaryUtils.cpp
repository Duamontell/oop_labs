#include "Dictionary.h"
#include "FileUtils.h"
#include "StringUtils.h"

const std::string DELIMITER_IN_FILE = ":";
const std::string TRANSLATION_OUTPUT_DELIMITER = ", ";
const std::string AGREE_BIG = "Y";
const std::string AGREE_SMALL = "y";

void FillDictionaries(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, const std::string& line)
{
	size_t delPos = line.find(DELIMITER_IN_FILE);
	std::string engWord = line.substr(0, delPos);
	std::string rusWord = line.substr(delPos + 1);

	dictionaryEngRus.insert({ ToLower(engWord), rusWord });
	dictionaryRusEng.insert({ ToLower(rusWord), engWord });
}

void ImportDictionary(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::istream& dictionaryFile)
{
	std::string line;
	while (std::getline(dictionaryFile, line))
	{
		FillDictionaries(dictionaryEngRus, dictionaryRusEng, line);
	}
}

void SaveDictionary(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::string fileName)
{
	std::ofstream dictionary = GetOutputFile(fileName);
	for (auto it = dictionaryEngRus.begin(); it != dictionaryEngRus.end(); ++it)
	{
		const std::string& engWord = it->first;
		const std::string& rusTranslation = it->second;
		auto range = dictionaryRusEng.equal_range(ToLower(rusTranslation));
		for (auto it = range.first; it != range.second; ++it)
		{
			if (ToLower(it->second) == engWord)
			{
				dictionary << it->second << DELIMITER_IN_FILE << rusTranslation << "\n";
				break;
			}
		}
	}
}

bool IsExitCommand(const std::string& line)
{
	return line == "...";
}

void AskSave(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::string fileName)
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string userInput;
	std::getline(std::cin, userInput);
	if (userInput == AGREE_BIG || userInput == AGREE_SMALL)
	{
		SaveDictionary(dictionaryEngRus, dictionaryRusEng, fileName);
		std::cout << "Изменения сохранены. До свидания." << std::endl;
	}
}

std::string AskAboutAddWord(const std::string& word)
{
	std::cout << "Неизвестное слово \"" << word << "\".Введите перевод или пустую строку для отказа.\n";
	std::string userInput;
	std::getline(std::cin, userInput);
	if (userInput.empty())
	{
		std::cout << "Слово \"" << word << "\" проигнорировано\n";
	}
	return userInput;
}

void AddTranslation(std::multimap<std::string, std::string>& dictionarySourceTarget,
	std::multimap<std::string, std::string>& dictionaryTargetSource, const std::string& word,
	const std::string& translate)
{
	dictionarySourceTarget.insert({ ToLower(word), translate });
	dictionaryTargetSource.insert({ ToLower(translate), word });
	std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translate << "\".\n";
}

std::string GetTranslations(const std::multimap<std::string, std::string>& dictionary,
	const std::string& word)
{
	auto range = dictionary.equal_range(word);
	std::string result;
	for (auto i = range.first; i != range.second; ++i)
	{
		if (!result.empty())
		{
			result += TRANSLATION_OUTPUT_DELIMITER;
		}
		result += i->second;
	}

	return result;
}

std::string FindTranslation(const std::multimap<std::string, std::string>& dictionary,
	const std::string& word)
{
	std::string wordLow = ToLower(word);
	auto range = dictionary.equal_range(wordLow);
	if (range.first != range.second)
	{
		return GetTranslations(dictionary, wordLow);
	}
	return "";
}

std::string SearchWord(std::multimap<std::string, std::string>& dictionarySourceTarget,
	std::multimap<std::string, std::string>& dictionaryTargetSource,
	const std::string& word, bool& isDictChanged)
{
	std::string result;
	result = FindTranslation(dictionarySourceTarget, word);
	if (result.empty())
	{
		std::string userAnswer = AskAboutAddWord(word);
		if (!userAnswer.empty())
		{
			isDictChanged = true;
			AddTranslation(dictionarySourceTarget, dictionaryTargetSource, word, userAnswer);
		}
	}
	return result;
}

std::string ProcessWord(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, const std::string& word, bool& isDictChanged)
{
	if (word.empty())
	{
		std::cout << "Введите слово!";
		return "";
	}

	std::string result;
	if (IsEnglish(word))
	{
		result = SearchWord(dictionaryEngRus, dictionaryRusEng, word, isDictChanged);
	}
	else
	{
		result = SearchWord(dictionaryRusEng, dictionaryEngRus, word, isDictChanged);
	}
	return result;
}

void RunUserDialog(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::string fileName)
{
	std::string line;
	bool isDictChanged = false;
	while (std::getline(std::cin, line))
	{
		std::string cleanedLine = StringTrim(line);
		if (!IsExitCommand(cleanedLine))
		{
			std::string translatedWord = ProcessWord(dictionaryEngRus, dictionaryRusEng, cleanedLine, isDictChanged);
			std::cout << translatedWord << "\n";
		}
		else
		{
			break;
		}
	}
	if (isDictChanged)
	{
		AskSave(dictionaryEngRus, dictionaryRusEng, fileName);
	}
}
