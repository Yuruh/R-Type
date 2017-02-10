//
// Created by yuruh on 30/12/16.
//

#include <Serializable/JoystickEvent.hpp>

JoystickEvent::JoystickEvent()
{
    this->_type = EVENT_JOYSTICK;
}

JoystickEvent::~JoystickEvent()
{

}

std::string JoystickEvent::serialize() const
{
    size_t          i = 0;
    unsigned int    lenData = sizeof(this->x) + sizeof(this->y);
    char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

    memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    memcpy(data + i, &(this->x), sizeof(this->x));
    i += sizeof(this->x);
    memcpy(data + i, &(this->y), sizeof(this->y));
    i += sizeof(this->y);
    ret.assign(data, i);
    delete[] data;

    return (ret);
}

void JoystickEvent::operator<<(const char *bytes)
{
    size_t  it = 0;
    size_t  len;

    this->_type = static_cast<PacketType>(this->parseType<uint32_t>(bytes, it));
    it += 4;
    len = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->x = this->parseType<float>(bytes, it);
    it += sizeof(this->x);
    this->y = this->parseType<float>(bytes, it);
    it += sizeof(this->y);
//    this->_buttonType = this->parseType<ButtonType>(bytes, it);
}

ISerializable *JoystickEvent::clone() const
{
    return nullptr;
}
