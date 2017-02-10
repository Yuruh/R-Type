#include 	"RTypeParserHelper.hpp"
#include 	"ParserError.hpp"

RTypeParserHelper::RTypeParserHelper(size_t &nbLine) : _nbLine(nbLine) {
}

RTypeParserHelper::~RTypeParserHelper() {

}

bool 		RTypeParserHelper::isDouble(const std::string &str) const {
	size_t	found;

	if (str.find_first_not_of("-0123456789.") != std::string::npos)
		return (false);
	else if (str[0] == '.' || str[str.size() - 1] == '.')
		return (false);
	if ((found = str.find(".")) != std::string::npos &&
		(str.find(".", found + 1) != std::string::npos))
		return (false);
	return (true);
}

void 		RTypeParserHelper::checkNewLine(const char &c) const {
	if (c == '\n')
		this->_nbLine++;
}

std::string RTypeParserHelper::tagName(const std::string &str, size_t it) const {
	std::string 	name = "";

	it++;
	if (str[it] == '>' || str[it] == '<' || !str[it])
		throw ParserError("Invalid tag at line "+std::to_string(this->_nbLine));
	while (str[it] && str[it] != '<' && str[it] != '>') {
		if (str[it] != '/')
			name += str[it];
		it++;
	}
	if (!str[it] || str[it] == '<')
		throw ParserError("Tag not closed at line "+std::to_string(this->_nbLine));
	return (name);
}

std::string RTypeParserHelper::tagValue(const std::string &str, size_t it) const {
	std::string 	value = "";

	if (str[it] == '>' || str[it] == '<' || !str[it])
		throw ParserError("Invalid tag value at line "+std::to_string(this->_nbLine));
	while (str[it] && str[it] != '<' && str[it] != '>') {
		value += str[it];
		it++;
	}
	if (!str[it] || str[it] == '>')
		throw ParserError("Invalid tag value at line "+std::to_string(this->_nbLine));
	return (value);
}

bool 		RTypeParserHelper::tagClosing(const std::string &str, size_t it) const {
	return (str[it + 1] == '/');
}

void 		RTypeParserHelper::passTag(const std::string &str, size_t &it) const {
	while (str[it] && str[it] != '>')
		it++;
	if (str[it])
		it++;
}

void 		RTypeParserHelper::passTagValue(const std::string &str, size_t &it) const {
	while (str[it] && str[it] != '<')
		it++;
}

std::string RTypeParserHelper::translatePattern(Pattern::type type) {
	std::map<Pattern::type, std::string> 	patterns;

	patterns[Pattern::Linear] = "Linear";
	return (patterns[type]);
}
