//
// Created by yuruh on 29/11/16.
//

#ifndef RTYPE_INETWORK_HPP
#define RTYPE_INETWORK_HPP

#include <Threadable.hpp>

class INetwork : public Threadable
{
public:
    virtual void    clientConnected(uint16_t port) = 0;

    virtual void    clientRegistered(uint16_t port) = 0;

    virtual void    connectClient() = 0;

    virtual void    createGame() = 0;

    virtual void    launchGame(uint32_t) = 0;

    virtual void    sendButtonEvent(const ButtonEvent &event) = 0;

    virtual void requireGameList() = 0;

    virtual void requireRoomInfo() = 0;

    virtual void joinGame(uint32_t gameId)= 0;

    virtual void leaveRoom(uint32_t gameId) = 0;

    virtual void leaveGame() = 0;

    virtual void sendJoystickEvent(const JoystickEvent &event) = 0;
};

#endif //RTYPE_INETWORK_HPP
