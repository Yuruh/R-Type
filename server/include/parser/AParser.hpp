#ifndef 		APARSER_HPP_
# define 		APARSER_HPP_

# include 		<iostream>
# include 		<fstream>
# include 		"IParser.hpp"
# include 		"ParserError.hpp"

class  			AParser : public IParser
{
public:
	AParser();
	virtual ~AParser();

	virtual void 	parse(const std::string&) = 0;
	std::string 	getFileContent() const;

protected:
	size_t 			_nbLine;
	std::string 	_fileContent;
	size_t 			_it;

	void	openFile(const std::string&);
};

#endif