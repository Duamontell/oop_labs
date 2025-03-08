#include "HtmlDecode.h"

int main()
{
	try
	{
		std::string html;
		while (std::getline(std::cin, html))
		{
			std::cout << HtmlDecode(html) << "\n";
		}
	}
	catch (const std::exception&)
	{
	}
}
