#include "Serializable/SimpleInfo.hpp"

SimpleInfo::SimpleInfo() {
	this->_type = UNDEFINED;
}

SimpleInfo::SimpleInfo(PacketType type)
{
	this->_type = type;
}

SimpleInfo::~SimpleInfo()
{

}

std::string SimpleInfo::serialize() const
{
	size_t          i = 0;
   	uint32_t       lenData = 0;
   	char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;
  	
  	memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);

    ret.assign(data, i);
    delete[] data;

    return (ret);
}

void 			SimpleInfo::operator<<(const char *bytes)
{
    unsigned int  it = 0;

    this->_type = static_cast<PacketType>(this->parseType<uint32_t>(bytes, it));
}

ISerializable* 		SimpleInfo::clone() const
{
    ISerializable* 	clone = new SimpleInfo(this->_type);

    return (clone);
}

std::ostream& 	operator<<(std::ostream &os, const SimpleInfo &client) {
    os << "PACKET TYPE = " << client.getType();
    return (os);
}