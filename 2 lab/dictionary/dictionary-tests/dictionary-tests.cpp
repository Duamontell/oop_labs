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
	REQUIRE(ToLower("������") == "������");
	REQUIRE(ToLower("�����") == "�����");
	REQUIRE(ToLower("") == "");
}

TEST_CASE("Get translations from dictionary english -> russian")
{
	std::multimap<std::string, std::string> dictionary = {
		{ "cat", "�����" }, { "cat", "���" }, { "elephant", "����" }, { "one two three", "���� ��� ���" }
	};
	std::string word = "cat";
	REQUIRE(GetTranslations(dictionary, word) == "�����, ���");
	word = "elephant";
	REQUIRE(GetTranslations(dictionary, word) == "����");
	word = "one two three";
	REQUIRE(GetTranslations(dictionary, word) == "���� ��� ���");
}

TEST_CASE("Get translations from dictionary russian -> english")
{
	std::multimap<std::string, std::string> dictionary = {
		{ "�������", "saturday" }, { "���", "cat" }, { "��������", "call names" }, { "�����", "caT" }
	};
	std::string word = "���";
	REQUIRE(GetTranslations(dictionary, word) == "cat");
	word = "��������";
	REQUIRE(GetTranslations(dictionary, word) == "call names");
	word = "�����";
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
	std::string testLine = "MEAT:����";
	FillDictionaries(dictionaryEngRus, dictionaryRusEng, testLine);
	SECTION("check dictionaryEngRus pair ('meat', '����')")
	{
		auto range = dictionaryEngRus.equal_range("meat");
		bool found = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "����")
			{
				found = true;
				break;
			}
		}
		REQUIRE(found);
	}
	SECTION("check dictionaryRusEng pair ('����', 'MEAT')")
	{
		auto range = dictionaryRusEng.equal_range("����");
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
	std::istringstream iss("meET:�����\nSPOON:�����");

	ImportDictionary(dictionaryEngRus, dictionaryRusEng, iss);
	SECTION("check dictionaryEngRus pair ('meet', '�����')")
	{
		auto range = dictionaryEngRus.equal_range("meet");
		bool foundHello = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == "�����")
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
			if (it->second == "�����")
			{
				foundWorld = true;
				break;
			}
		}
		REQUIRE(foundWorld);
	}
	SECTION("check dictionaryRusEng pair")
	{
		auto range = dictionaryRusEng.equal_range("�����");
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

		range = dictionaryRusEng.equal_range("�����");
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
