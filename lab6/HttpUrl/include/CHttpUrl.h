#ifndef CHTTPURL_H
#define CHTTPURL_H
#include <string>

enum class Protocol
{
    HTTP,
    HTTPS
};
using Port = unsigned short;

class CHttpUrl
{
public:
    CHttpUrl(std::string const& url);

    CHttpUrl
    (
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP
    );

    CHttpUrl
    (
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        Port port
    );

    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    Port GetPort() const;

    static std::string MapProtocolToPortName(Protocol protocol);
    static bool IsValidPort(int port);
    friend std::ostream& operator<<(std::ostream& output, CHttpUrl const& rhs)
    {
        output << std::endl;
        output << "URL: " << rhs.GetURL() << std::endl;
        output << "PROTOCOL: " << MapProtocolToPortName(rhs.GetProtocol()) << std::endl;
        output << "DOMAIN: " << rhs.GetDomain() << std::endl;
        output << "PORT: " << rhs.GetPort() << std::endl;
        output << "DOC: " << rhs.GetDocument() << std::endl;
        output << std::endl;

        return output;
    }
private:
    constexpr static Port MIN_PORT = 1;
    constexpr static Port MAX_PORT = 65535;
    constexpr static Port DEFAULT_HTTP_PORT = 80;
    constexpr static Port DEFAULT_HTTPS_PORT = 443;
    constexpr static std::string DEFAULT_HTTP_PORT_NAME = "http";
    constexpr static std::string DEFAULT_HTTPS_PORT_NAME = "https";
    constexpr static std::string PROTOCOL_HOST_SEPARATOR = "://";
    const char SLASH_SEPARATOR = '/';
    const char COLON_SEPARATOR = ':';

    std::string m_domain;
    std::string m_document;
    Protocol m_protocol;
    Port m_port;

    std::string ParseDomain(std::string const& domain);
    std::string ParseDocument(std::string const& document);
    Protocol ParseProtocol(std::string const& protocol);
    Port ParsePort(std::string const& port);

    static Port MapProtocolToPort(Protocol protocol);
};

#endif //CHTTPURL_H
