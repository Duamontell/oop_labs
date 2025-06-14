#include <gtest/gtest.h>
#include "CHttpUrl.h"

// Доделать тесты
TEST(CHttpUrlConstructortorTest, ParsesHttpWithDocumentTest)
{
    CHttpUrl url("http://example.com/index.html");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/index.html");
    EXPECT_EQ(url.GetURL(), "http://example.com/index.html");
}

TEST(CHttpUrlConstructortorTest, ParsesHttpsWithoutPortTest)
{
    CHttpUrl url("HTTPS://example.com");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/");
    EXPECT_EQ(url.GetURL(), "https://example.com/");
}

TEST(CHttpUrlConstructortorTest, ParsesHttpWithPortTest)
{
    CHttpUrl url("http://example.com:8080/user");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/user");
    EXPECT_EQ(url.GetURL(), "http://example.com:8080/user");
}

TEST(CHttpUrlParsingTest, ProtocolCaseInsensitiveTest)
{
    CHttpUrl url1("HtTp://a.ru");
    CHttpUrl url2("hTtPs://a.ru");
    EXPECT_EQ(url1.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url2.GetProtocol(), Protocol::HTTPS);
}

TEST(CHttpUrlParsingTest, MissingDelimiterTest)
{
    EXPECT_THROW(CHttpUrl("http:/example.com"),std::invalid_argument);
}

TEST(CHttpUrlParsingTest, ThrowsOnInvalidProtocolTest)
{
    EXPECT_THROW(CHttpUrl("fgtp://example.com"),std::invalid_argument);
}

TEST(CHttpUrlParsingTest, ThrowsOnNonDigitPortTest)
{
    EXPECT_THROW(CHttpUrl("http://example.com:8r80"),std::invalid_argument);
}

TEST(CHttpUrlParsingTest, ThrowsOnPortOutOfRangeTest)
{
    EXPECT_THROW(CHttpUrl("http://example.com:0"),std::invalid_argument);
    EXPECT_NO_THROW(CHttpUrl("http://example.com:1"));
    EXPECT_NO_THROW(CHttpUrl("http://example.com:65535"));
    EXPECT_THROW(CHttpUrl("http://example.com:65536"), std::invalid_argument);
    EXPECT_THROW(CHttpUrl("http://example.com:70000"),std::invalid_argument);
}

TEST(CHttpUrlParsingTest, ThrowsOnEmptyDomainWithDocumentTest)
{
    EXPECT_THROW(CHttpUrl("http:///path"),std::invalid_argument);
}

TEST(CHttpUrlConstructortorTest, DomainDocumentProtocolAddsSlashTest)
{
    CHttpUrl url("example.org", "gdg/svv/sds", Protocol::HTTPS);
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.org");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/gdg/svv/sds");
    EXPECT_EQ(url.GetURL(), "https://example.org/gdg/svv/sds");

    EXPECT_THROW(CHttpUrl("", "/doc", Protocol::HTTP), std::invalid_argument);
}

TEST(CHttpUrlConstructortorTest, DomainDocumentProtocolPortTest)
{
    CHttpUrl url("example.org", "/doc", Protocol::HTTP, 821);
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.org");
    EXPECT_EQ(url.GetPort(), 821);
    EXPECT_EQ(url.GetDocument(), "/doc");
    EXPECT_EQ(url.GetURL(), "http://example.org:821/doc");

    EXPECT_THROW(CHttpUrl("example.org", "/doc", Protocol::HTTP, 0),std::invalid_argument);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}