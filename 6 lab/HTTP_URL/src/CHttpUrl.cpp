#include "CHttpUrl.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "CUrlParsingError.h"

CHttpUrl::CHttpUrl(std::string const &url)
{
	// Разбить на функции поменьше
	// Протокола может не быть
	size_t protocolPos = url.find("://");
	if (protocolPos == std::string::npos)
	{
		throw CUrlParsingError("No protocol delimiter '://' found");
	}
	std::string protocol = url.substr(0, protocolPos);
	m_protocol = ParseProtocol(protocol);

	std::string restUrl = url.substr(protocolPos + 3);
	size_t docPos = restUrl.find('/');
	std::string authority = (docPos == std::string::npos) ? restUrl : restUrl.substr(0, docPos);
	m_document = (docPos == std::string::npos ? "/" : restUrl.substr(docPos));

	auto portPos = authority.find(':');
	if (portPos == std::string::npos)
	{
		m_domain = authority;
		m_port = (m_protocol == Protocol::HTTP ? HTTP_DEFAULT_PORT : HTTPS_DEFAULT_PORT);
	}
	else
	{
		m_domain = authority.substr(0, portPos);
		std::string portStr = authority.substr(portPos + 1);
		m_port = ParsePort(portStr);
	}

	if (m_domain.empty() && !m_document.empty())
	{
		throw CUrlParsingError("Domain is empty");
	}
	m_document = NormalizeDocument(m_document);
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol) :
	m_protocol(protocol),
	m_domain(domain),
	m_document(NormalizeDocument(document)),
	m_port(protocol == Protocol::HTTP ? HTTP_DEFAULT_PORT : HTTPS_DEFAULT_PORT)
{
	if (domain.empty() && !document.empty())
	{
		throw CUrlParsingError("Domain is empty");
	}
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol, unsigned short port) :
	m_protocol(protocol),
	m_domain(domain),
	m_document(NormalizeDocument(document)),
	m_port(port)
{
	if (domain.empty() && !document.empty())
	{
		throw CUrlParsingError("Domain is empty");
	}
	if (!ValidePort(port))
	{
		throw CUrlParsingError("Invalid port number");
	}
}

std::string CHttpUrl::GetURL() const
{
	std::ostringstream oss;
	oss << (m_protocol == Protocol::HTTP ? "http" : "https")
		<< "://"
		<< m_domain;
	if ((m_port != HTTP_DEFAULT_PORT || m_protocol != Protocol::HTTP) && (
		    m_port != HTTPS_DEFAULT_PORT || m_protocol != Protocol::HTTPS))
	{
		oss << ":" << m_port;
	}
	oss << m_document;
	return oss.str();
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

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::ParseProtocol(const std::string& protocol)
{
	std::string lower;
	lower.resize(protocol.size());
	std::transform(protocol.begin(), protocol.end(), lower.begin(), ::tolower);

	if (lower == "http") return Protocol::HTTP;
	if (lower == "https") return Protocol::HTTPS;
	throw CUrlParsingError("Invalid protocol: " + protocol);
}

unsigned short CHttpUrl::ParsePort(const std::string& port)
{
	if (port.empty()) throw CUrlParsingError("Empty port");
	for (char c : port)
	{
		if (!std::isdigit(c)) throw CUrlParsingError("Port contains not a number character");
	}
	int portNumber = std::stoi(port);
	if (!ValidePort(portNumber)) throw CUrlParsingError("Port out of range");
	return static_cast<unsigned short>(portNumber);
}

std::string CHttpUrl::NormalizeDocument(const std::string& document)
{
	return document[0] != '/' ? "/" + document : document;
}

bool CHttpUrl::ValidePort(int port)
{
	return port >= PORT_MIN_NUMBER && port <= PORT_MAX_NUMBER;
}
