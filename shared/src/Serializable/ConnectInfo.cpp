//
// Created by yuruh on 19/12/16.
//

#include "Serializable/ConnectInfo.hpp"

ConnectInfo::ConnectInfo()
{
    this->_type = CONNECT;
    this->port = 0;
}

ConnectInfo::~ConnectInfo()
{

}

std::string ConnectInfo::serialize() const
{
    size_t          i = 0;
    unsigned int    lenData = sizeof(this->port) + sizeof(this->errorCode);
    char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

    memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    memcpy(data + i, &(this->port), sizeof(this->port));
    i += sizeof(this->port);
    memcpy(data + i, &(this->errorCode), sizeof(this->errorCode));
    i += sizeof(this->errorCode);

    ret.assign(data, i);
    delete[] data;

    return (ret);
}

void ConnectInfo::operator<<(const char *bytes)
{
    unsigned int  it = 0;

    this->_type = this->parseType<PacketType>(bytes, it);
    it += sizeof(this->_type);
//    this->parseType<uint32_t>(bytes, it);
    it += sizeof(uint32_t);
    this->port = this->parseType<uint16_t>(bytes, it);
    it += sizeof(this->port);
    this->errorCode = this->parseType<uint32_t>(bytes, it);
}

ISerializable *ConnectInfo::clone() const
{
    ISerializable *clone = new ConnectInfo();

    return (clone);
}

std::ostream& 	operator<<(std::ostream &os, const ConnectInfo &client)
{
    os << "PACKET TYPE = " << client.getType() << " PORT = " << client.port << " ERROR_CODE = " << client.errorCode;
    return (os);
}
