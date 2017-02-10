#include "Serializable/ASerializable.hpp"

PacketType 		ASerializable::getType() const {
	return (this->_type);
}

ASerializable::ASerializable()
{
    this->_type = UNDEFINED;
    this->errorCode = 0;
}
