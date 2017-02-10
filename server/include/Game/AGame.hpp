//
// Created by wasta-geek on 14/12/16.
//

#ifndef SERVER_RTYPE_IGAME_HPP
#define SERVER_RTYPE_IGAME_HPP

#include <Entities/APlayable.hpp>
#include <vector>
#include <list>
#include "ButtonEvent.hpp"

class AGame
{
public:
    AGame(uint32_t id);
    virtual ~AGame() {};

    virtual bool connectPlayer(uint32_t);
    virtual void disconnectPlayer(uint32_t);
    virtual void joystickUsed(float, float, uint32_t) = 0;
    virtual void startGame() = 0;
    virtual void useButtonEvent(const ButtonEvent &buttonEvent, uint32_t)=0;
    virtual void useJoystickEvent(const JoystickEvent &buttonEvent, uint32_t)=0;
    virtual bool isGameOver() = 0;
    virtual bool isLevelOver() = 0;
    virtual bool isGameEmpty() = 0;
    virtual void update(float) = 0;

    bool        isStarted();
    bool        containPlayer(uint32_t playerId) const;
    uint32_t    getId() const;

    const GameList getRoomInfo() const;
    void        leaveRoom(uint32_t);

protected:
    std::vector<APlayable *> _players;
    uint32_t _id;
    std::list<EntityType> _availablesType;
    bool     _isStarted;

};

extern std::mutex g_mutex;


#endif //SERVER_RTYPE_IGAME_HPP
