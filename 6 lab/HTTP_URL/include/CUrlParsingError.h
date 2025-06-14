#ifndef CURLPARSINGERROR_H
#define CURLPARSINGERROR_H
#include <stdexcept>


class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(const std::string& errorText)
			: std::invalid_argument(errorText) {}
};


#endif //CURLPARSINGERROR_H
