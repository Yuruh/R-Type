//
// Created by yuruh on 15/12/16.
//

#ifndef SHARED_CHIEFINTERPRETER_HPP
#define SHARED_CHIEFINTERPRETER_HPP


#include "IInterpreter.hpp"
#include "../Serializable/ISerializable.hpp"

class ChiefInterpreter : public IInterpreter
{
private:
    static ChiefInterpreter    _instance;
    IInterpreter        *subInterpreter;
    ChiefInterpreter();
    ~ChiefInterpreter();

public:
    void setSubInterpreter(IInterpreter *);
    void interpretPacket(const char *, PacketType, unsigned int id);

    static ChiefInterpreter &getInstance();
};


#endif //SHARED_CHIEFINTERPRETER_HPP
