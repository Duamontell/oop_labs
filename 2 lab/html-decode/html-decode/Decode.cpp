#include "HtmlDecode.h"

#include <map>

const std::map<std::string, char> entities = {
	{ "&quot;", '"' },
	{ "&apos;", '\'' },
	{ "&lt;", '<' },
	{ "&gt;", '>' },
	{ "&amp;", '&' }
};

std::string DecodeEntity(const std::string& entity, bool& found)
{
	auto itr = entities.find(entity);
	if (itr != entities.end())
	{
		found = false;
		return std::string(1, itr->second);
	}
	return entity;
}

void CheckEntity(char ch, std::string& decode, std::string& entity, bool& found)
{
	if (ch == ';')
	{
		decode += DecodeEntity(entity, found);
		entity.clear();
	}
	else if (ch == '&')
	{
		decode += entity.substr(0, entity.size() - 1);
		entity = entity.substr(entity.size() - 1, entity.size());
	}
}

std::string HtmlDecode(const std::string& html)
{
	std::string decode;
	std::string entity;
	bool found = false;
	for (size_t i = 0; i < html.size(); ++i)
	{
		if (found)
		{
			entity += html[i];
			CheckEntity(html[i], decode, entity, found);
		}
		else if (html[i] == '&')
		{
			found = true;
			entity = html[i];
		}
		else
		{
			decode += html[i];
		}
	}

	if (found)
	{
		decode += entity;
	}

	return decode;
}