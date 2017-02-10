#include "Serializable/ButtonEvent.hpp"

ButtonEvent::ButtonEvent() {
    this->_type = UNDEFINED;
    this->_buttonType = UNKNOWN_BUTTON;
}

ButtonEvent::ButtonEvent(PacketType type) {
    this->_type = type;
    this->_buttonType = UNKNOWN_BUTTON;
}

ButtonEvent::~ButtonEvent() {

}

void        ButtonEvent::setButtonType(ButtonType button)
{
    _buttonType = button;
}

ButtonType ButtonEvent::getButtonType(void) const
{
    return _buttonType;
}

std::string ButtonEvent::serialize() const
{
	size_t          i = 0;
    unsigned int    lenData = sizeof(this->_buttonType);
    char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

    memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    memcpy(data + i, &(this->_buttonType), sizeof(this->_buttonType));
    i += sizeof(this->_buttonType);
    ret.assign(data, i);
    delete[] data;
    return (ret);

}

void 		ButtonEvent::operator<<(const char *bytes) {
	size_t  it = 0;
    size_t  len;

    this->_type = static_cast<PacketType>(this->parseType<uint32_t>(bytes, it));
    it += 4;
    len = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->_buttonType = this->parseType<ButtonType>(bytes, it);
}

ISerializable* 	ButtonEvent::clone() const {
	ISerializable*    clone = new ButtonEvent(this->_type);

    return (clone);
}

std::ostream& 	operator<<(std::ostream &os, const ButtonEvent &buttonEvent) {
	os << "PACKET TYPE = " << buttonEvent.getType() << std::endl <<
            "BUTTON_TYPE = " << buttonEvent.getButtonType() << std::endl;
	return (os);
}
