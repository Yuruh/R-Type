//
// Created by yuruh on 15/12/16.
//

#ifndef SHARED_IINTERPRETER_HPP
#define SHARED_IINTERPRETER_HPP

#include "../Serializable/ISerializable.hpp"

class IInterpreter
{
public:
    virtual void interpretPacket(const char *, PacketType type, uint32_t id)= 0;
};
#endif //SHARED_IINTERPRETER_HPP
