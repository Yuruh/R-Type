#ifndef		PARSER_ERROR_HPP_
# define	PARSER_ERROR_HPP_

#include	<string>
#include	<exception>

class ParserError : public std::exception
{
protected:
	std::string	_msg;

public:
	ParserError(std::string) throw();
	~ParserError();

	const char	*what() const throw();
};

#endif