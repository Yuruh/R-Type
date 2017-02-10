#ifndef 		RTYPE_PARSER_HPP_
# define 		RTYPE_PARSER_HPP_

# include 		<vector>
# include 		<map>
# include		<parser/Factory/EntityFactory.hpp>
# include 		"AParser.hpp"
# include 		"RTypeParserHelper.hpp"
# include 		"Chunk.hpp"
# include 		"AEntity.hpp"

class 			RTypeParser : public AParser
{
public:
	RTypeParser(std::vector<IChunk*>&);
	~RTypeParser();
	
	void 		parse(const std::string&);
	void 		parseChunk();
	void 		parseEntity(IChunk*, const std::string&);
	void 		parseProp(const std::string&, std::map<std::string, float>&);

private:
	RTypeParserHelper* 					_helper;
	std::vector<IChunk*>&				_chunks;
	std::map<std::string, EntityType> _entityLinks;
};

std::ostream 		&operator<<(std::ostream&, const std::vector<IChunk*>&);

#endif