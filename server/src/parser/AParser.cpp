#include 	"AParser.hpp"

AParser::AParser() {
	this->_nbLine = 1;
	this->_fileContent = "";
	this->_it = 0;
}

AParser::~AParser() {

}

void 		AParser::openFile(const std::string &filePath) {
	std::fstream	file;
	std::string		line;

	file.open(filePath.c_str());
	if (!file.is_open())
		throw ParserError("Couldn't open the file " + filePath);
	while (std::getline(file, line))
		this->_fileContent += line + "\n";
	file.close();
}

std::string AParser::getFileContent() const {
	return (this->_fileContent);
}