#include <iostream>
#include <regex>
#include <cassert>
#include "../include/CUrlParsingError.h"
#include "../include/CHttpUrl.h"

const std::string DOCUMENT_REGULAR_EXPRESSION = R"(^(((?:\/)*([^\s]*))*)$)";
const std::string DOMAIN_REGULAR_EXPRESSION = R"(^([\w-]{1,63}(?:\.[\w-]{1,63})*)$)";
const std::string URL_REGULAR_EXPRESSION = R"(^(https|http)://([\w-]{1,63}(?:\.[\w-]{1,63})*)(?:(?::)(\d{1,5}))?(?:(?:/)([^\s]*))*$)";

constexpr unsigned MATCHES_COUNT = 5;
constexpr unsigned PROTOCOL_MATCH = 1;
constexpr unsigned HOST_MATCH = 2;
constexpr unsigned PORT_MATCH = 3;
constexpr unsigned DOCUMENT_MATCH = 4;

std::string StringToLowerCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c)
		{
			return std::tolower(c);
		}
	);
	return str;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	const std::regex urlRegExp(URL_REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch matches;
	bool matchesFound = regex_search(url, matches, urlRegExp);

	if (matches.size() != MATCHES_COUNT)
	{
		throw CUrlParsingError("unknown url format");
	}

	m_protocol = ParseProtocol(matches[PROTOCOL_MATCH]);
	m_port = ParsePort(matches[PORT_MATCH]);
	m_domain = matches[HOST_MATCH];
	m_document = ParseDocument(matches[DOCUMENT_MATCH]);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	m_protocol = protocol;
	try
	{
		m_domain = ParseDomain(domain);
		m_port = MapProtocolToPort(m_protocol);
		m_document = ParseDocument(document);
	}
	catch (std::exception const& e)
	{
		throw std::invalid_argument(e.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, Port port)
	: CHttpUrl(domain, document, protocol)
{
	if (!IsValidPort(port))
	{
		throw CUrlParsingError("invalid port");
	}

	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string protocol = MapProtocolToPortName(m_protocol);
	bool urlHasCustomPort = m_port != DEFAULT_HTTP_PORT && m_port != DEFAULT_HTTPS_PORT;
	std::string url = protocol + PROTOCOL_HOST_SEPARATOR + m_domain;

	if (urlHasCustomPort)
	{
		url += COLON_SEPARATOR + std::to_string(m_port);
	}

	url += m_document;
	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

Port CHttpUrl::GetPort() const
{
	return m_port;
}

//TODO передача по константной ссылке
Port CHttpUrl::MapProtocolToPort(Protocol protocol)
{
	switch (protocol)
	{
		case Protocol::HTTP:
			return DEFAULT_HTTP_PORT;
		case Protocol::HTTPS:
			return DEFAULT_HTTPS_PORT;
		default:
			//TODO runtime exception
			return 0;
	}
}

std::string CHttpUrl::MapProtocolToPortName(Protocol protocol)
{
	switch (protocol)
	{
		case Protocol::HTTP:
			return DEFAULT_HTTP_PORT_NAME;
		case Protocol::HTTPS:
			return DEFAULT_HTTPS_PORT_NAME;
		default:
			//TODO runtime exception
			assert(false);
	}
}

Protocol CHttpUrl::ParseProtocol(std::string const& protocol)
{
	std::string caseInsensitiveProtocol = StringToLowerCase(protocol);

	if (caseInsensitiveProtocol == DEFAULT_HTTP_PORT_NAME)
	{
		return Protocol::HTTP;
	}

	if (caseInsensitiveProtocol == DEFAULT_HTTPS_PORT_NAME)
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("error while parsing protocol");
}

std::string CHttpUrl::ParseDomain(std::string const& domain)
{
	const std::regex domainRegExp(DOMAIN_REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch matches;
	bool matchesFound = regex_search(domain, matches, domainRegExp);

	if (!matchesFound)
	{
		throw CUrlParsingError("invalid domain");
	}

	return matches[1];
}

Port CHttpUrl::ParsePort(std::string const& port)
{
	if (port.empty())
	{
		return MapProtocolToPort(m_protocol);
	}

	try
	{
		int parsedPort = stoi(port);
		if (!IsValidPort(parsedPort))
		{
			throw CUrlParsingError("error while parsing port");
		}
		return static_cast<Port>(parsedPort);
	}
	catch (std::exception const&)
	{
		throw CUrlParsingError("error while parsing port");
	}
}

std::string CHttpUrl::ParseDocument(std::string const& document)
{
	const std::regex documentRegExp(DOCUMENT_REGULAR_EXPRESSION, std::regex_constants::icase);
	std::smatch matches;
	bool matchesFound = regex_search(document, matches, documentRegExp);

	if (!matchesFound)
	{
		throw CUrlParsingError("invalid document");
	}
	std::string parsedDocument = matches[1];

	if (parsedDocument[0] != SLASH_SEPARATOR)
	{
		parsedDocument = SLASH_SEPARATOR + parsedDocument;
	}

	return parsedDocument;
}

bool CHttpUrl::IsValidPort(int port)
{
	return port >= MIN_PORT && port <= MAX_PORT;
}