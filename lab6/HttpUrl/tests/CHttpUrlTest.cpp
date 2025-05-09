#include <gtest/gtest.h>
#include "../include/CHttpUrl.h"
#include "../include/CUrlParsingError.h"

TEST(CHttpUrlTest, ConstructorWithFullUrl)
{
    CHttpUrl url("https://example.com:8080/path/to/resource");
    
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/path/to/resource");
    EXPECT_EQ(url.GetURL(), "https://example.com:8080/path/to/resource");
}

TEST(CHttpUrlTest, ConstructorWithDefaultHttpPort)
{
    CHttpUrl url("http://example.com/path");
    
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetURL(), "http://example.com/path");
}

TEST(CHttpUrlTest, ConstructorWithDefaultHttpsPort)
{
    CHttpUrl url("https://example.com/path");
    
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetURL(), "https://example.com/path");
}

TEST(CHttpUrlTest, ConstructorWithEmptyDocument)
{
    CHttpUrl url("http://example.com");
    
    EXPECT_EQ(url.GetDocument(), "/");
    EXPECT_EQ(url.GetURL(), "http://example.com/");
}

TEST(CHttpUrlTest, ConstructorWithInvalidUrl)
{
    EXPECT_THROW(CHttpUrl("invalid_url"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl("http://"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl("https://example.com:99999/path"), CUrlParsingError);
}

TEST(CHttpUrlTest, ComponentConstructorWithHttp)
{
    CHttpUrl url("example.com", "/path", Protocol::HTTP);
    
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/path");
}

TEST(CHttpUrlTest, ComponentConstructorWithHttps)
{
    CHttpUrl url("example.com", "/path", Protocol::HTTPS);
    
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetPort(), 443);
}

TEST(CHttpUrlTest, ComponentConstructorWithCustomPort)
{
    CHttpUrl url("example.com", "/path", Protocol::HTTP, 8080);
    
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetURL(), "http://example.com:8080/path");
}

TEST(CHttpUrlTest, ComponentConstructorWithInvalidDomain)
{
    EXPECT_THROW(CHttpUrl("", "/path", Protocol::HTTP), std::invalid_argument);
    EXPECT_THROW(CHttpUrl("invalid domain", "/path", Protocol::HTTP), std::invalid_argument);
}

TEST(CHttpUrlTest, ComponentConstructorWithInvalidPort)
{
    EXPECT_THROW(CHttpUrl("example.com", "/path", Protocol::HTTP, 0), CUrlParsingError);
    EXPECT_THROW(CHttpUrl("example.com", "/path", Protocol::HTTP, 65536), CUrlParsingError);
}

TEST(CHttpUrlTest, MapProtocolToString)
{
    EXPECT_EQ(CHttpUrl::MapProtocolToPortName(Protocol::HTTP), "http");
    EXPECT_EQ(CHttpUrl::MapProtocolToPortName(Protocol::HTTPS), "https");
}

TEST(CHttpUrlTest, IsValidPort)
{
    EXPECT_TRUE(CHttpUrl::IsValidPort(1));
    EXPECT_TRUE(CHttpUrl::IsValidPort(8080));
    EXPECT_TRUE(CHttpUrl::IsValidPort(65535));
    EXPECT_FALSE(CHttpUrl::IsValidPort(0));
    EXPECT_FALSE(CHttpUrl::IsValidPort(65536));
}

TEST(CHttpUrlTest, UrlWithQueryParameters)
{
    CHttpUrl url("http://example.com/path?param=value");
    EXPECT_EQ(url.GetDocument(), "/path?param=value");
}

TEST(CHttpUrlTest, UrlWithFragment)
{
    CHttpUrl url("http://example.com/path#section");
    EXPECT_EQ(url.GetDocument(), "/path#section");
}

TEST(CHttpUrlTest, UrlWithInvalidProtocol)
{
    EXPECT_THROW(CHttpUrl("ftp://example.com"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl("httpx://example.com"), CUrlParsingError);
}

TEST(CHttpUrlTest, CaseInsensitiveProtocol)
{
    EXPECT_NO_THROW(CHttpUrl("HTTP://example.com"));
    EXPECT_NO_THROW(CHttpUrl("hTtP://example.com"));
    EXPECT_NO_THROW(CHttpUrl("HTTPS://example.com"));
    //todo проверить, что действительно нижний кейс
}