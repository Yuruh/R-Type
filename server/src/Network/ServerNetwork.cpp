//
// ServerNetwork.cpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/server/src/Network/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Sun Dec 11 22:23:51 2016 Raphael Thiebault
// Last update Sat Dec 31 03:28:54 2016 Wasta-Geek
//

#include	<stdexcept>
#include	<algorithm>
#include	<iostream>
#ifdef __linux__
#include        <sys/poll.h>
#define POLL poll
#elif _WIN32
#include        <WinSock2.h>
#define POLL WSAPoll
#endif
#include    <Serializable/ConnectInfo.hpp>
#include    <Serializable/GameInfo.hpp>
#include <Serializable/SimpleInfo.hpp>
#include <Core.hpp>
#include	"Network/ServerNetwork.hpp"


ServerNetwork::ServerNetwork(uint16_t port, bool ssl) {
    this->addHandler(new TcpSocket());
    if (!(handlers.back()->doBind(port) && handlers.back()->doListen()))
        throw std::runtime_error("Error while creating tcp server");
    std::cout << "  Now Listening on port " << port << std::endl;
    this->addHandler(new UdpSocket());
    if (!handlers.back()->doBind(0))
        throw std::runtime_error("Error while creating udp server");
    pool.start();
    std::cout << "  Now Listening on port " << handlers.back()->getPort() << std::endl;
}

ServerNetwork::~ServerNetwork() {
    pool.stop();
    std::for_each(handlers.begin(), handlers.end(), [this](ISocket *s) { delete s; });
}

ISocket*	ServerNetwork::addHandler(ISocket *socket)
{
    handlers.push_back(socket);

    fds.emplace_back();
    fds.back().fd = socket->getFd();
    fds.back().events = POLLIN;

    return (socket);
}

ISocket*	ServerNetwork::addConnection(ISocket *socket)
{
    socket->setId(clientId);

    this->addHandler(socket);

    std::cerr << "  New connection - " << socket->getFd() << std::endl;

    connected[clientId] = socket;

    clientId++;
    return (socket);
}

void        ServerNetwork::removeConnection(int clientId)
{
//    todo : use leave room ?
    if (connected.find(clientId) != connected.end()) {
        Core::getInstance().useLeaveGame((uint32_t) clientId);
        std::cerr << "  Connection closed" << std::endl;
        delete connected[clientId];
        connected.erase(clientId);
        if (in_game.find(clientId) != in_game.end()) {
            delete in_game[clientId];
            in_game.erase(clientId);
        }
    }
}

void ServerNetwork::run()
{
    unsigned long   size = 0;
    std::vector<uint32_t>           info;
    std::map<std::vector<uint32_t>, uint32_t>::iterator it;
    std::string     message;
    int             i;

    while (running) {
      if ((i = POLL(&fds[0], fds.size(), 20)) < 0)
            throw std::runtime_error("Error while polling sockets");
	if (i == 0)
	  continue;
        if (fds[0].revents == POLLIN || fds[0].revents == POLLRDNORM) {
            info = handlers[0]->doAccept();
            if (!info.empty())
                this->addConnection(new TcpSocket(info[0]));
        }
        if (fds[1].revents == POLLIN || fds[1].revents == POLLRDNORM) {
            info = handlers[1]->doAccept();
            message = handlers[1]->doRecvFrom();

            if (!info.empty() && ((it = address_book.find(info)) != address_book.end()))
                pool.enqueue(&ASocket::packetize, message, it->second);
        }

        size = fds.size();
        for (i = 2; i < size; i++) {
            if (fds[i].revents == POLLIN || fds[i].revents == POLLRDNORM) {
                message = handlers[i]->doRecv();
                if (message.empty()) {
                    this->removeConnection(handlers[i]->getId());
                    fds.erase(fds.begin() + i);
                    handlers.erase(handlers.begin() + i);
                }
                else
                     pool.enqueue(&ASocket::packetize, message, handlers[i]->getId());
            }
        }
    }
}

void ServerNetwork::clientConnected(uint32_t clientId, uint16_t port)
{
    if (connected.find(clientId) != connected.end()) {
        in_game[clientId] = new UdpSocket();
        in_game[clientId]->doConnect(connected[clientId]->getIp(), port);
        in_game[clientId]->setId(clientId);

        std::cout << "  Connected to " <<  connected[clientId]->getIp() << " on port " << port << std::endl;

        ConnectInfo ping;

        ping.port = handlers[1]->getPort();
        ping.errorCode = 0;

        connected[clientId]->doSend(ping.serialize());
    }
}

void ServerNetwork::clientRegistered(uint32_t clientId, uint16_t port) {
    if (connected.find(clientId) != connected.end()) {
        address_book[std::vector<uint32_t>({connected[clientId]->getAddr(), port})] = clientId;

        std::cout << "  Registered on " <<  connected[clientId]->getIp() << " on port " << port << std::endl;

        ConnectInfo pong;

        pong.port = in_game[clientId]->getPort();
        pong.errorCode = 1;

        connected[clientId]->doSend(pong.serialize());
    }
}

void ServerNetwork::sendEntityPos(uint32_t playerId, const EntityPos &pos)
{
    if (in_game.find(playerId) != in_game.end()) {
        in_game[playerId]->doSend(pos.serialize());
    }
}

void ServerNetwork::sendGameList(uint32_t id, const GameList &gameList)
{
    if (connected.find(id) != connected.end())
        connected[id]->doSend(gameList.serialize());
    else
        std::cerr << "ERROR GAME LIST" << std::endl;
}

void ServerNetwork::sendGameInfo(uint32_t gameId, uint32_t playerId)
{
    GameInfo    gameInfo(GAME_JOINED);

    gameInfo.setGameId(gameId);
    connected[playerId]->doSend(gameInfo.serialize());
}

void ServerNetwork::sendGameLaunched(uint32_t gameId, uint32_t playerId)
{
    GameInfo    gameInfo(GAME_LAUNCHED);

    gameInfo.setGameId(gameId);
    if (connected.find(playerId) != connected.end())
        connected[playerId]->doSend(gameInfo.serialize());
    else
        std::cerr << "ERROR GAME LAUNCH" << std::endl;
}

void ServerNetwork::sendEndGame(bool isVictory, uint32_t playerId)
{
    if (connected.find(playerId) == connected.end())
        return;
    if (isVictory)
        connected[playerId]->doSend(SimpleInfo(GAME_WON).serialize());
    else
        connected[playerId]->doSend(SimpleInfo(GAME_LOST).serialize());
}
