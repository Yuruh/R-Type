#include "Serializable/GameInfo.hpp"

GameInfo::GameInfo() {
	this->_type = UNDEFINED;
    this->_playerId = 0;
    this->_gameId = 0;
}

GameInfo::GameInfo(PacketType type) {
	this->_type = type;
    this->_playerId = 0;
    this->_gameId = 0;
}

GameInfo::~GameInfo(){

}

uint32_t 		GameInfo::getPlayerId() const {
	return (this->_playerId);
}

void 			GameInfo::setPlayerId(uint32_t playerId) {
	this->_playerId = playerId;
}

uint32_t 		GameInfo::getGameId() const {
	return (this->_gameId);
}

void 			GameInfo::setGameId(uint32_t gameId) {
	this->_gameId = gameId;
}

std::string GameInfo::serialize() const {
	size_t          i = 0;
   	unsigned int    lenData = sizeof(this->_playerId) + sizeof(this->_gameId);
   	char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

   	memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    memcpy(data + i, &(this->_playerId), sizeof(this->_playerId));
    i += sizeof(this->_playerId);
    memcpy(data + i, &(this->_gameId), sizeof(this->_gameId));
    i += sizeof(this->_gameId);
    ret.assign(data, i);
    delete[] data;

    return (ret);
}

void 			GameInfo::operator<<(const char *bytes) {
	size_t  it = 0;
    size_t  len;

    this->_type = this->parseType<PacketType>(bytes, it);
    it += 4;
    len = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->_playerId = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->_gameId = this->parseType<uint32_t>(bytes, it);
}

ISerializable*        GameInfo::clone() const {
    ISerializable*    clone = new GameInfo(this->_type);
    
    return (clone);
}

std::ostream& 	operator<<(std::ostream &os, const GameInfo &game) {
	os << "PACKET TYPE = " << game.getType() << 
			" PLAYER_ID =  " << game.getPlayerId() <<
			" GAME_ID = " << game.getGameId();
	return (os);
}