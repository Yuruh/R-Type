//
// Created by wasta-geek on 13/12/16.
//

#ifndef SERVER_RTYPE_CORE_HPP
#define SERVER_RTYPE_CORE_HPP

#include <Serializable/JoystickEvent.hpp>
#include    "Game/GameManager.hpp"
#include    "Network/ServerNetwork.hpp"

class Core
{
public:
    ~Core();

    void run(uint16_t);

    void sendEntityPositions(uint32_t, const EntityPos&);

    void connectClient(uint32_t id, uint16_t port);

    void registerClient(uint32_t id, uint16_t port);

    void createGame(uint32_t playerId);

    void joinGame(uint32_t playerId, uint32_t gameId);

    void launchGame(uint32_t gameId);

    static Core &getInstance();

    void useButtonEvent(uint32_t playerId, const ButtonEvent &buttonEvent);

    void useJoystickEvent(uint32_t playerId, const JoystickEvent &buttonEvent);

    void sendGameList(uint32_t id);

    void sendGameInfo(uint32_t gameId, uint32_t playerId);

    void sendGameLaunched(uint32_t gameId, uint32_t);

    void sendRoomInfo(uint32_t playerId);

    void notifyLeaveRoom(uint32_t playerId, uint32_t gameId);

    void sendEndGame(bool isVictory, uint32_t playerId);

    void useLeaveGame(uint32_t playerId);

private:
    Core();
    INetwork *_network;
    GameManager _gameManager;
    static  Core        _instance;
    void    catchShutdown();

};


#endif //SERVER_RTYPE_CORE_HPP
