#ifndef 		IPARSER_HPP_
# define 		IPARSER_HPP_

# include		<string>

class  			IParser
{
public:
	IParser(){};
	virtual ~IParser(){};
	
	virtual void 	parse(const std::string&) = 0;

protected:
	virtual void	openFile(const std::string&) = 0;
};

#endif