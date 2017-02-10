#include "ParserError.hpp"

ParserError::ParserError(std::string msg) throw() : _msg("Parser Error: " + msg)
{
}

ParserError::~ParserError()
{
}

const char		*ParserError::what() const throw()
{
	return (this->_msg.c_str());
}