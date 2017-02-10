//
// Created by yuruh on 15/12/16.
//

#include "ChiefInterpreter.hpp"

ChiefInterpreter  ChiefInterpreter::_instance = ChiefInterpreter();

ChiefInterpreter::ChiefInterpreter()
{
    this->subInterpreter = nullptr;
}

ChiefInterpreter::~ChiefInterpreter()
{
//    if (this->subInterpreter != nullptr)
//        delete this->subInterpreter;
}

void ChiefInterpreter::setSubInterpreter(IInterpreter *interpreter)
{
    if (this->subInterpreter != nullptr)
        delete this->subInterpreter;
    this->subInterpreter = interpreter;
}

void ChiefInterpreter::interpretPacket(const char *data, PacketType type, unsigned int id)
{
    if (this->subInterpreter != nullptr)
        this->subInterpreter->interpretPacket(data, type, id);
    else
      std::cerr << "[ERROR] Interpreter not set" << std::endl;
}

ChiefInterpreter &ChiefInterpreter::getInstance()
{
    return _instance;
}
