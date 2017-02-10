//
// Created by yuruh on 26/12/16.
//

#include "Serializable/GameList.hpp"

GameList::GameList()
{
    this->_type = UNDEFINED;
}

GameList::GameList(PacketType type)
{
    this->_type = type;
}

GameList::~GameList()
{

}

std::string GameList::serialize() const
{
    size_t          i = 0;
    unsigned int    lenData = sizeof(uint32_t) * this->gameIDs.size();
    char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

    memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    for (unsigned int j = 0; j < this->gameIDs.size(); ++j)
    {
        memcpy(data + i, &(this->gameIDs[j]), sizeof(this->gameIDs[j]));
        i += sizeof(this->gameIDs[j]);
    }
    ret.assign(data, i);
    delete[] data;

    return (ret);
}

void GameList::operator<<(const char *bytes)
{
    uint32_t  it = 0;
    uint32_t      len;

    this->gameIDs.clear();

    this->_type = this->parseType<PacketType>(bytes, it);
    it += sizeof(this->_type);
    len = this->parseType<uint32_t>(bytes, it);
    it += sizeof(uint32_t);
    while (it < len + sizeof(this->_type) + sizeof(len))
    {
        this->gameIDs.push_back(this->parseType<uint32_t>(bytes, it));
        it += sizeof(uint32_t);
    }
}

ISerializable *GameList::clone() const
{
    ISerializable *clone = new GameList();

    return (clone);
}

std::ostream& 	operator<<(std::ostream &os, const GameList &gl)
{
    os << "PACKET TYPE = " << gl.getType() << " IDS = ";

    for (unsigned int i = 0; i < gl.gameIDs.size(); ++i)
        os << gl.gameIDs[i] << " ";
    return (os);
}