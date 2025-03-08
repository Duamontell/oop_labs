#pragma once

#include <cctype>
#include <iosfwd>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::string ToLower(const std::string& word);
void FillDictionaries(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, const std::string& line);
void ImportDictionary(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::istream& dictionaryFile);
void SaveDictionary(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::string fileName);
bool IsExitCommand(const std::string& line);
std::string GetTranslations(const std::multimap<std::string, std::string>& dictionary, const std::string& word);
std::string FindTranslation(const std::multimap<std::string, std::string>& dictionary,
	const std::string& word);
std::string SearchWord(std::multimap<std::string, std::string>& dictionarySourceTarget,
	std::multimap<std::string, std::string>& dictionaryTargetSource,
	const std::string& word, bool& isDictChanged);
std::string ProcessWord(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, const std::string& word, bool& isDictChanged);
void RunUserDialog(std::multimap<std::string, std::string>& dictionaryEngRus,
	std::multimap<std::string, std::string>& dictionaryRusEng, std::string fileName);