//
// Created by raphicci on 12/19/16.
//

#pragma once

#include	<vector>
#include <Serializable/ButtonEvent.hpp>
#include <Serializable/JoystickEvent.hpp>
#include	"INetwork.hpp"
#include	"ThreadPool.hpp"
#include	"Network/TcpSocket.hpp"
#include	"Network/UdpSocket.hpp"

class ClientNetwork : public INetwork
{
protected:
    std::map<std::vector<uint32_t>, uint32_t >    address_book;
    std::vector<ISocket *>      handlers;
    std::vector<struct pollfd>  fds;
    ThreadPool                  pool;
    std::string                 hostname;

private:
    void    addHandler(ISocket *socket);

public:
    ClientNetwork(const std::string &hostname, uint16_t port, bool ssl = true);
    ~ClientNetwork();

    void    run();
    void    clientConnected(uint16_t port);
    void    clientRegistered(uint16_t port);
    void    connectClient();
    void    registerClient();
    void    createGame();
    void    launchGame(uint32_t);
    void    sendButtonEvent(const ButtonEvent &event);
    void    sendJoystickEvent(const JoystickEvent &event);
    void    requireGameList();
    void    requireRoomInfo();
    void    joinGame(uint32_t gameId);
    void    leaveRoom(uint32_t gameId);
    void    leaveGame();


};
