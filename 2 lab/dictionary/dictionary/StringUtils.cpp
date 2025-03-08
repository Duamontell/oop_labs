#include "StringUtils.h"
#include "Dictionary.h"

std::string ToLower(const std::string& word)
{
	std::string result = word;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}

std::string StringTrim(const std::string& line)
{
	auto start = std::find_if(line.begin(), line.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	});
	if (start == line.end())
	{
		return "";
	}

	auto end = std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base();

	return std::string(start, end);
}

bool IsEnglish(const std::string& word)
{
	return (word[0] >= 'A' && word[0] <= 'Z') || (word[0] > 'a' && word[0] <= 'z');
}