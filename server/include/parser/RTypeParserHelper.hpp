#ifndef 		RTYPE_PARSER_HELPER_HPP_
# define 		RTYPE_PARSER_HELPER_HPP_

# include 		<iostream>
# include 		<string>
# include		<parser/Factory/EntityFactory.hpp>

class 			RTypeParserHelper
{
public:
	RTypeParserHelper(size_t &);
	~RTypeParserHelper();
	
	bool 		isDouble(const std::string&) const;
	void 		checkNewLine(const char&) const;
	std::string tagName(const std::string&, size_t) const;
	std::string tagValue(const std::string&, size_t) const;
	bool 		tagClosing(const std::string&, size_t) const;
	void 		passTag(const std::string&, size_t&) const;
	void 		passTagValue(const std::string&, size_t&) const;

	static std::string	translatePattern(Pattern::type);

private:
	size_t 		&_nbLine;
};

#endif