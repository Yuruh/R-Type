//
// ClientInterpreter.cpp for  in /home/yuruh/rendu/cpp/rtype/shared/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Dec 13 12:53:12 2016 Antoine Lempereur
// Last update Fri Dec 23 11:18:43 2016 Antoine Lempereur
//

#include <Core.hpp>
#include <Serializable/ConnectInfo.hpp>
#include <Serializable/SimpleInfo.hpp>
#include "ClientInterpreter.hpp"

ClientInterpreter::ClientInterpreter()
{
    this->packets[ENTITY_POS] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretEntityPos, this, std::placeholders::_1));
    this->packets[DEATH_ENTITY] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretEntityPos, this, std::placeholders::_1));
    this->packets[CONNECT] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretConnection, this, std::placeholders::_1));
    this->packets[GAME_LIST] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretGameList, this, std::placeholders::_1));
    this->packets[GAME_JOINED] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretGameJoined, this, std::placeholders::_1));
    this->packets[GAME_LAUNCHED] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretGameLaunched, this, std::placeholders::_1));
    this->packets[ROOM_INFO] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretRoomInfo, this, std::placeholders::_1));
    this->packets[GAME_WON] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretGameResult, this, std::placeholders::_1));
    this->packets[GAME_LOST] = std::function<void(const char*)>(std::bind(&ClientInterpreter::interpretGameResult, this, std::placeholders::_1));
}

ClientInterpreter::~ClientInterpreter()
{

}

void  ClientInterpreter::interpretGameLaunched(const char *data)
{
    GameInfo instance(GAME_LAUNCHED);
    instance << data;

    Core::getInstance().useGameInfo(instance);
}

void  ClientInterpreter::interpretGameJoined(const char *data)
{
    GameInfo instance(GAME_JOINED);
    instance << data;

    Core::getInstance().useGameInfo(instance);
}

void  ClientInterpreter::interpretEntityPos(const char *data)
{
    EntityPos instance(ENTITY_POS);
    instance << data;

    Core::getInstance().useEntityPos(instance);
}

void ClientInterpreter::interpretPacket(const char *data, PacketType type, uint32_t)
{
    if (this->packets.find(type) != this->packets.end())
      this->packets[type](data);
    else
        std::cerr << "Packet ID= " << type << " not interpreted" << std::endl;
}

void ClientInterpreter::interpretConnection(const char *data)
{
    ConnectInfo instance;

    instance << data;

//    std::cout << "Connection info: \n" << instance << std::endl;
    if (instance.errorCode)
        Core::getInstance().registerServer(instance.port);
    else
        Core::getInstance().connectServer(instance.port);
}

void ClientInterpreter::interpretGameList(const char *data)
{
    GameList    gameList;

    gameList << data;

    Core::getInstance().useGameList(gameList);
}

void ClientInterpreter::interpretRoomInfo(const char *data)
{
    GameList    roomInfo;

    roomInfo << data;

    Core::getInstance().useGameList(roomInfo);
}

void ClientInterpreter::interpretGameResult(const char *data)
{
    SimpleInfo  simpleInfo;

    simpleInfo << data;

    Core::getInstance().useGameResult(simpleInfo);
}