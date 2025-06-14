#ifndef CHTTPURL_H
#define CHTTPURL_H
#include <string>


enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в эту строку
	// не должен включаться
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	const unsigned short HTTP_DEFAULT_PORT = 80;
	const unsigned short HTTPS_DEFAULT_PORT = 443;
	const unsigned short PORT_MIN_NUMBER = 1;
	const unsigned short PORT_MAX_NUMBER = 65535;

	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	Protocol ParseProtocol(const std::string& protocol);
	unsigned short ParsePort(const std::string& port);
	std::string NormalizeDocument(const std::string& document);
	bool ValidePort(int port);
};

#endif //CHTTPURL_H
