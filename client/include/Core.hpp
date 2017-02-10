//
// Created by yuruh on 29/11/16.
//

#ifndef RTYPE_CORE_HPP
#define RTYPE_CORE_HPP

#include <EntityPos.hpp>
#include <ButtonEvent.hpp>
#include <Serializable/GameList.hpp>
#include <Serializable/JoystickEvent.hpp>
#include "IEventManager.hpp"
#include "Network/ClientNetwork.hpp"
#include "display/IDisplay.hpp"
#include "display/TextureManager.hpp"

class Core
{
private:
    Core();

    INetwork            *network;
    IEventManager       *eventManager;
    IDisplay            *display;

    static  Core        _instance;
public:
    ~Core();
    static Core &getInstance();

    void run(const std::string &, uint16_t);

    void useEntityPos(const EntityPos &entityPos);

    void useJoystickEvent(const JoystickEvent &joystickEvent);

    void useButtonEvent(const ButtonEvent &buttonEvent);

    void connectServer(uint16_t port);

    void registerServer(uint16_t port);

    void requireGameList();

    void requireRoomInfo();

    void useGameList(const GameList &gameList);

    void sendCreateGame();

    void sendLaunchGame(uint32_t gameId);

    void sendJoinGame(uint32_t gameId);

    void sendLeaveRoom(uint32_t gameId);

    void sendLeaveGame();

    void useGameInfo(const GameInfo &gameInfo);

    void useGameResult(const SimpleInfo &simpleInfo);
};


#endif //RTYPE_CORE_HPP
