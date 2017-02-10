 	#include 	"RTypeParser.hpp"

RTypeParser::RTypeParser(std::vector<IChunk*> &chunks) : _chunks(chunks) {
	this->_helper = new RTypeParserHelper(this->_nbLine);
	this->_entityLinks["monster"] = MONSTERS;
	this->_entityLinks["bonus"] = BONUS;
	this->_entityLinks["decorative"] = DECORATIVE;
}

RTypeParser::~RTypeParser() {

}

void 			RTypeParser::parse(const std::string &filePath) {
	this->openFile(filePath);
	while (this->_fileContent[this->_it]) {
		this->_helper->checkNewLine(this->_fileContent[this->_it]);
		if (this->_fileContent[this->_it] == '<' &&
			this->_helper->tagName(this->_fileContent, this->_it) == "chunk")
			this->parseChunk();
		else
			throw(ParserError("Tag name <chunk> expected at line "+std::to_string(this->_nbLine)));
		this->_it++;
	}
}

void 			RTypeParser::parseChunk() {
	IChunk 		*chunk = new Chunk();
	std::string tagName;

	if (this->_helper->tagClosing(this->_fileContent, this->_it))
		throw(ParserError("Tag <chunk> closed before opened at line "+std::to_string(this->_nbLine)));	
	this->_helper->passTag(this->_fileContent, this->_it);
	while (this->_fileContent[this->_it]) {
		this->_helper->checkNewLine(this->_fileContent[this->_it]);
		if (this->_fileContent[this->_it] == '<') {
			tagName = this->_helper->tagName(this->_fileContent, this->_it);
			if (tagName == "chunk") {
				if (this->_helper->tagClosing(this->_fileContent, this->_it)) {
					this->_helper->passTag(this->_fileContent, this->_it);
					this->_chunks.push_back(chunk);
					return;
				}
				else
					throw(ParserError("Tag <chunk> opened in another one at line "+std::to_string(this->_nbLine)));
			}
			else if (this->_entityLinks.find(tagName) != this->_entityLinks.end())
				this->parseEntity(chunk, tagName);
			else
				throw(ParserError("Unknown tag <"+tagName+"> for chunk at line "+std::to_string(this->_nbLine)));

		}
		else
			this->_it++;
	}
	throw(ParserError("Tag name <chunk> never closed at line "+std::to_string(this->_nbLine)));
}

void 			RTypeParser::parseEntity(IChunk *chunk, const std::string &category) {
	std::string 							tagName;
	std::map<std::string, float>			props;

	if (this->_helper->tagClosing(this->_fileContent, this->_it))
		throw(ParserError("Tag <"+category+"> closed before opened at line "+std::to_string(this->_nbLine)));
	this->_helper->passTag(this->_fileContent, this->_it);
	while (this->_fileContent[this->_it]) {
		this->_helper->checkNewLine(this->_fileContent[this->_it]);
		if (this->_fileContent[this->_it] == '<') {
			tagName = this->_helper->tagName(this->_fileContent, this->_it);
			if (tagName == category) {
				if (this->_helper->tagClosing(this->_fileContent, this->_it)) {
					this->_helper->passTag(this->_fileContent, this->_it);

					 ANonPlayable* newEntity = EntityFactory::getInstance()->
                            createInitializedEntity(this->_entityLinks[category], props);
                    if (newEntity != NULL)
    					chunk->addContents(newEntity);
					return;
				}
				else
					throw(ParserError("Tag <"+category+"> opened in another one at line "+std::to_string(this->_nbLine)));
			}
			else if (tagName == "id" || tagName == "x" || 
					tagName == "y" || tagName == "pattern" ||
					tagName == "firstplan" || tagName == "size" ||
					tagName == "speed")
				this->parseProp(tagName, props);
			else
				throw(ParserError("Unknown tag <"+tagName+"> for entity at line "+std::to_string(this->_nbLine)));
		}
		else
			this->_it++;
	}
	throw(ParserError("Tag name <"+category+"> never closed at line "+std::to_string(this->_nbLine)));
}

void 			RTypeParser::parseProp(const std::string &prop, std::map<std::string, float> &props) {
	std::string tagName;
	std::string tagValue;

	if (this->_helper->tagClosing(this->_fileContent, this->_it))
		throw(ParserError("Tag <"+prop+"> closed before opened at line "+std::to_string(this->_nbLine)));
	this->_helper->passTag(this->_fileContent, this->_it);
	tagValue = this->_helper->tagValue(this->_fileContent, this->_it);
	if (!this->_helper->isDouble(tagValue))
		throw(ParserError(tagValue+" for "+prop+" is not a good double at line "+std::to_string(this->_nbLine)));
	props[prop] = std::stof(tagValue);
	this->_helper->passTagValue(this->_fileContent, this->_it);
	tagName = this->_helper->tagName(this->_fileContent, this->_it);
	if (tagName != prop)
		throw(ParserError("Closing tag </"+prop+"> expected, got tag name "+tagName+" instead at line "+std::to_string(this->_nbLine)));
	if (!this->_helper->tagClosing(this->_fileContent, this->_it))
		throw(ParserError("Tag <"+prop+"> opened in another one at line "+std::to_string(this->_nbLine)));
	else
		this->_helper->passTag(this->_fileContent, this->_it);
}

std::ostream 		&operator<<(std::ostream &os, const std::vector<IChunk*> &chunks) {
	std::vector<ANonPlayable*>	entities;

	for (size_t it = 0; it < chunks.size(); it++) {
		os << "Chunk n°" << it << std::endl;
		entities = chunks[it]->getContents();
		for (size_t itEntity = 0; itEntity < entities.size(); itEntity++) {
			os << "Entity n°" << itEntity << " is a " << std::endl;
			os << "It's on " << entities[itEntity]->getX() << " and " << entities[itEntity]->getY() << std::endl;
			os << "Its speed scale is " << entities[itEntity]->getSpeedScale() << " and its size scale is " << entities[itEntity]->getSizeScale() << std::endl;
			os << "Its pattern is " << RTypeParserHelper::translatePattern(entities[itEntity]->getPattern()) << std::endl;
		}
		os << "--------------------------------------------------------------" << std::endl;
	}
	return (os);
}