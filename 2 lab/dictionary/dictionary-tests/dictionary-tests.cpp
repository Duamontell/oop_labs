#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/ConsoleUtils.h"
#include "../dictionary/Dictionary.h"
#include "../dictionary/FileUtils.h"
#include "../dictionary/StringUtils.h"

TEST_CASE("Clean user line")
{
	REQUIRE(StringTrim("  Cat  tac  ") == "Cat  tac");
	REQUIRE(StringTrim("tac  ") == "tac");
	REQUIRE(StringTrim("    yom") == "yom");
	REQUIRE(StringTrim("dog") == "dog");
	REQUIRE(StringTrim(" ") == "");
	REQUIRE(StringTrim("") == "");
}

TEST_CASE("to lower string")
{
	setlocale(LC_ALL, "Ru");
	REQUIRE(ToLower("FRONT") == "front");
	REQUIRE(ToLower(" отяра") == "кот€ра");
	REQUIRE(ToLower("шайба") == "шайба");
	REQUIRE(ToLower("") == "");
}

TEST_CASE("Get translations from dictionary english -> russian")
{
	std::multimap<std::string, std::string> dictionary = {
		{ "cat", "кќш ј" }, { "cat", " ќт" }, { "elephant", "слон" }, { "one two three", "один ƒ¬ј “ри" }
	};
	std::string word = "cat";
	REQUIRE(GetTranslations(dictionary, word) == "кќш ј,  ќт");
	word = "elephant";
	REQUIRE(GetTranslations(dictionary, word) == "слон");
	word = "one two three";
	REQUIRE(GetTranslations(dictionary, word) == "один ƒ¬ј “ри");
}

TEST_CASE("Get translations from dictionary russian -> english")
{
	std::multimap<std::string, std::string> dictionary = {
		{ "суббота", "saturday" }, { "кот", "cat" }, { "обзывать", "call names" }, { "кошка", "caT" }
	};
	std::string word = "кот";
	REQUIRE(GetTranslations(dictionary, word) == "cat");
	word = "обзывать";
	REQUIRE(GetTranslations(dictionary, word) == "call names");
	word = "кошка";
	REQUIRE(GetTranslations(dictionary, word) == "caT");
}

TEST_CASE("enter command line")
{
	REQUIRE(IsExitCommand("...") == true);
	REQUIRE(IsExitCommand(".. ") == false);
	REQUIRE(IsExitCommand("sssdsdadasd") == false);
	REQUIRE(IsExitCommand("") == false);
}

TEST_CASE("fill dictionary using line")
{
	std::multimap<std::string, std::string> dictionaryEngRus;
	std::multimap<std::string, std::string> dictionaryRusEng;
	std::string testLine = "MEAT:ћ€со";
	FillDictionaries(dictionaryEngRus, dictionaryRusEng, testLine);
	SECTION("check dictionaryEngRus pair ('meat', 'ћ€со')")
	{
		auto range = dictionaryEngRus.equal_range("meat");
		bool found = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "ћ€со")
			{
				found = true;
				break;
			}
		}
		REQUIRE(found);
	}
	SECTION("check dictionaryRusEng pair ('м€со', 'MEAT')")
	{
		auto range = dictionaryRusEng.equal_range("м€со");
		bool found = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "MEAT")
			{
				found = true;
				break;
			}
		}
		REQUIRE(found);
	}
}

TEST_CASE("check ImportDictionary read stream")
{
	std::multimap<std::string, std::string> dictionaryEngRus;
	std::multimap<std::string, std::string> dictionaryRusEng;
	std::istringstream iss("meET:мя— ќ\nSPOON:Ћќж ј");

	ImportDictionary(dictionaryEngRus, dictionaryRusEng, iss);
	SECTION("check dictionaryEngRus pair ('meet', 'мя— ќ')")
	{
		auto range = dictionaryEngRus.equal_range("meet");
		bool foundHello = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "мя— ќ")
			{
				foundHello = true;
				break;
			}
		}
		REQUIRE(foundHello);

		range = dictionaryEngRus.equal_range("spoon");
		bool foundWorld = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "Ћќж ј")
			{
				foundWorld = true;
				break;
			}
		}
		REQUIRE(foundWorld);
	}
	SECTION("check dictionaryRusEng pair")
	{
		auto range = dictionaryRusEng.equal_range("м€ско");
		bool foundHello = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "meET")
			{
				foundHello = true;
				break;
			}
		}
		REQUIRE(foundHello);

		range = dictionaryRusEng.equal_range("ложка");
		bool foundWorld = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "SPOON")
			{
				foundWorld = true;
				break;
			}
		}
		REQUIRE(foundWorld);
	}
}
