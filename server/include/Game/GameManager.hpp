//
// Created by wasta-geek on 14/12/16.
//

#ifndef SERVER_RTYPE_GAMEMANAGER_HPP
#define SERVER_RTYPE_GAMEMANAGER_HPP

#include <map>
#include <vector>
#include <Threadable.hpp>
#include <Serializable/GameList.hpp>
#include "AGame.hpp"
#include "Timer.hpp"

class GameManager : public Threadable
{
public:
    GameManager();
    ~GameManager();

    bool joinGame(uint32_t playerId, uint32_t gameId);
    void quitGame(uint32_t playerId, uint32_t gameId);
    void launchGame(uint32_t gameId);

    void createGame(uint32_t playerId);
    void run();

    void useButtonEvent(uint32_t playerId, const ButtonEvent &buttonEvent);
    void useJoystickEvent(uint32_t playerId, const JoystickEvent &event);

    const GameList getGameList() const;
    const GameList getRoomInfo(uint32_t playerId);
    void           notifyLeaveRoom(uint32_t playerId, uint32_t gameId);
    void           useLeaveGame(uint32_t playerId);
private:

    void updateGames();
private:
    static uint32_t     _gameId;
    Timer               _timer;
    std::vector<AGame*> _games;

    std::map<uint32_t, AGame*> _players;
};


#endif //SERVER_RTYPE_GAMEMANAGER_HPP
