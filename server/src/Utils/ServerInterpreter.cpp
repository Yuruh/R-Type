//
// Created by yuruh on 15/12/16.
//

#include <ButtonEvent.hpp>
#include <Serializable/ConnectInfo.hpp>
#include <Core.hpp>
#include <Serializable/GameInfo.hpp>
#include <Serializable/SimpleInfo.hpp>
#include <Serializable/JoystickEvent.hpp>
#include "ServerInterpreter.hpp"

ServerInterpreter::ServerInterpreter() {
    this->packets[EVENT_BUTTON] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretButtonEvent, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[EVENT_JOYSTICK] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretJoystickEvent, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[CONNECT] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretConnection, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[CREATE_GAME] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretCreateGame, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[JOIN_GAME] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretJoinGame, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[LAUNCH_GAME] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretLaunchGame, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[REQUIRE_GAME_LIST] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretRequireGameList, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[REQUIRE_ROOM_INFO] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretRequireRoomInfo, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[LEAVE_ROOM] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretLeaveRoom, this, std::placeholders::_1, std::placeholders::_2));
    this->packets[DISCONNECT_GAME] = std::function<void(const char *, uint32_t)>
            (std::bind(&ServerInterpreter::interpretDisconnectGame, this, std::placeholders::_1, std::placeholders::_2));
}

ServerInterpreter::~ServerInterpreter() {

}

void ServerInterpreter::interpretPacket(const char *data, PacketType type, uint32_t id)
{
    if (this->packets.find(type) != this->packets.end())
        this->packets[type](data, id);
    else
        std::cerr << "Packet ID= " << type << " not interpreted" << std::endl;
}

void ServerInterpreter::interpretButtonEvent(const char *data, uint32_t id)
{
    ButtonEvent instance(EVENT_BUTTON);

    instance << data;

    // std::cout << "[INTERPRETING BUTTON EVENT] : \n" << instance << std::endl;
    Core::getInstance().useButtonEvent(id, instance);
}

void ServerInterpreter::interpretJoystickEvent(const char *data, uint32_t id)
{
    JoystickEvent instance;

    instance << data;

    // std::cout << "[INTERPRETING BUTTON EVENT] : \n" << instance << std::endl;
    Core::getInstance().useJoystickEvent(id, instance);
}

void ServerInterpreter::interpretConnection(const char *data, uint32_t id)
{
    ConnectInfo instance;

    instance << data;

    std::cout << "Connection info: \n" << instance << std::endl;
    if (instance.errorCode)
        Core::getInstance().registerClient(id, instance.port);
    else
        Core::getInstance().connectClient(id, instance.port);
}

void ServerInterpreter::interpretCreateGame(const char *data, uint32_t id)
{
    GameInfo instance;

    instance << data;

    std::cout << "Game info [createGame]: \n" << instance << std::endl;
    Core::getInstance().createGame(id);
}

void ServerInterpreter::interpretJoinGame(const char *data, uint32_t id)
{
    GameInfo instance;

    instance << data;

    std::cout << "Game info[joinGame]: \n" << instance << std::endl;
    Core::getInstance().joinGame(id, instance.getGameId());
}

void ServerInterpreter::interpretLaunchGame(const char *data, uint32_t id)
{
    GameInfo instance;

    instance << data;

    std::cout << "Game info[launchGame]: \n" << instance << std::endl;
    Core::getInstance().launchGame(instance.getGameId());
}

void ServerInterpreter::interpretRequireGameList(const char *data, uint32_t id)
{
    SimpleInfo  instance;

    instance << data;

    Core::getInstance().sendGameList(id);
}

void ServerInterpreter::interpretRequireRoomInfo(const char *data, uint32_t id)
{
    SimpleInfo  instance;

    instance << data;

    Core::getInstance().sendRoomInfo(id);
}

void ServerInterpreter::interpretLeaveRoom(const char *data, uint32_t id)
{
    GameInfo  instance;

    instance << data;

    Core::getInstance().notifyLeaveRoom(id, instance.getGameId());
}

void ServerInterpreter::interpretDisconnectGame(const char *data, uint32_t id)
{
    SimpleInfo  instance;

    instance << data;

    Core::getInstance().useLeaveGame(id);
}
