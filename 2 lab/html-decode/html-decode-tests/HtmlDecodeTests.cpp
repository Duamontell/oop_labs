#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../html-decode/HtmlDecode.h"

TEST_CASE("HtmlDecode handles plain text")
{
	REQUIRE(HtmlDecode("Hello world!") == "Hello world!");
	REQUIRE(HtmlDecode("12345") == "12345");
}

TEST_CASE("HtmlDecode replaces single HTML entities")
{
	REQUIRE(HtmlDecode("&quot;") == "\"");
	REQUIRE(HtmlDecode("&apos;") == "'");
	REQUIRE(HtmlDecode("&lt;") == "<");
	REQUIRE(HtmlDecode("&gt;") == ">");
	REQUIRE(HtmlDecode("&amp;") == "&");
}

TEST_CASE("HtmlDecode handles multiple entities in a string")
{
	REQUIRE(HtmlDecode("5 &lt; 10 &amp;&amp; 10 &gt; 5") == "5 < 10 && 10 > 5");
	REQUIRE(HtmlDecode("Rock &amp; Stone!") == "Rock & Stone!");
	REQUIRE(HtmlDecode("&quot;Hello&quot;, he said.") == "\"Hello\", he said.");
}

TEST_CASE("HtmlDecode handles incomplete or unknown entities")
{
	REQUIRE(HtmlDecode("&quot") == "&quot");
	REQUIRE(HtmlDecode("&usddnk;") == "&usddnk;");
	REQUIRE(HtmlDecode("ds&&amp") == "ds&&amp");
	REQUIRE(HtmlDecode("Test &a") == "Test &a");
}

TEST_CASE("HtmlDecode handles mixed cases")
{
	REQUIRE(HtmlDecode("Tom & Jerry &gt; Rick &amp; Morty") == "Tom & Jerry > Rick & Morty");
	REQUIRE(HtmlDecode("A < B &gt; C") == "A < B > C");
}

TEST_CASE("HtmlDecode handles edge cases")
{
	REQUIRE(HtmlDecode("") == "");
	REQUIRE(HtmlDecode("&&&") == "&&&");
	REQUIRE(HtmlDecode("&;&;&;") == "&;&;&;");
	REQUIRE(HtmlDecode("&") == "&");
	REQUIRE(HtmlDecode("abbbb & cddd") == "abbbb & cddd");
}