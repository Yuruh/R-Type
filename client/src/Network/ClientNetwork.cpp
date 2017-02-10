//
// Created by raphicci on 12/19/16.
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
#include    <ConnectInfo.hpp>
#include <Serializable/GameInfo.hpp>
#include <Serializable/SimpleInfo.hpp>
#include	"Network/ClientNetwork.hpp"

ClientNetwork::ClientNetwork(const std::string &hostname, uint16_t port, bool ssl) : hostname(hostname) {
    this->addHandler(new TcpSocket());
    if (!(handlers.back()->doConnect(hostname, port)))
        throw std::runtime_error("Error while connecting tcp server");
    std::cout << "  Connected to " << hostname << " on port " << port << std::endl;
    this->addHandler(new UdpSocket());
    if (!(handlers.back()->doBind(0)))
        throw std::runtime_error("Error while connecting udp server");
    std::cout << "  Listening on port " << handlers.back()->getPort() << std::endl;
    pool.start(1);
}

ClientNetwork::~ClientNetwork() {
    pool.stop();
    std::for_each(handlers.begin(), handlers.end(), [this](ISocket *s) { delete s; });
}

void    ClientNetwork::addHandler(ISocket *socket)
{
    handlers.push_back(socket);

    fds.emplace_back();
    fds.back().fd = socket->getFd();
    fds.back().events = POLLIN;
}

void ClientNetwork::run()
{
    std::map<std::vector<uint32_t>, uint32_t>::iterator it;
    std::vector<uint32_t>   info;
    std::string             message;

    while (running) {
        if (POLL(&fds[0], fds.size(), -1) < 0)
            throw std::runtime_error("Error while polling sockets");

        if (fds[0].revents == POLLIN || fds[0].revents == POLLRDNORM) {
			message = handlers[0]->doRecv();
            if (message.empty()) return;
            pool.enqueue(&ASocket::packetize, message, handlers[0]->getId());
        }
		if (fds[1].revents == POLLIN || fds[1].revents == POLLRDNORM) {
			info = handlers[1]->doAccept();
			message = handlers[1]->doRecvFrom();

			if (!info.empty() && ((it = address_book.find(info)) != address_book.end()))
				pool.enqueue(&ASocket::packetize, message, it->second);
		}
    }
}

void ClientNetwork::clientConnected(uint16_t port) {
    handlers.push_back(new UdpSocket());
    handlers.back()->doConnect(handlers[0]->getIp(), port);

    std::cout << "  Connected to " <<  handlers[0]->getIp() << " on port " << port << std::endl;

    this->registerClient();
}

void ClientNetwork::clientRegistered(uint16_t port) {
    address_book[std::vector<uint32_t>({handlers[0]->getAddr(), port })] = 1;

    std::cout << "  Registered on " <<  handlers[0]->getIp() << " on port " << port << std::endl;
}

void ClientNetwork::connectClient() {
    ConnectInfo ping;

    ping.port = handlers[1]->getPort();
    ping.errorCode = 0;

    handlers[0]->doSend(ping.serialize());
}

void ClientNetwork::registerClient() {
    ConnectInfo pong;

    pong.port = handlers.back()->getPort();
    pong.errorCode = 1;

    handlers[0]->doSend(pong.serialize());
}

void ClientNetwork::createGame()
{
    GameInfo    gameInfo(CREATE_GAME);

    handlers[0]->doSend(gameInfo.serialize());
}

void ClientNetwork::launchGame(uint32_t gameId)
{
    GameInfo    gameInfo(LAUNCH_GAME);

    gameInfo.setGameId(gameId);
    handlers[0]->doSend(gameInfo.serialize());
}

void ClientNetwork::sendButtonEvent(const ButtonEvent &event)
{
    handlers[2]->doSend(event.serialize());
}

void ClientNetwork::requireGameList()
{
    SimpleInfo  info(REQUIRE_GAME_LIST);

    handlers[0]->doSend(info.serialize());
}

void ClientNetwork::requireRoomInfo()
{
    SimpleInfo  info(REQUIRE_ROOM_INFO);

    handlers[0]->doSend(info.serialize());
}

void ClientNetwork::joinGame(uint32_t gameId)
{
    GameInfo    gameInfo(JOIN_GAME);

    gameInfo.setGameId(gameId);
    handlers[0]->doSend(gameInfo.serialize());
}

void ClientNetwork::leaveRoom(uint32_t gameId)
{
    GameInfo    gameInfo(LEAVE_ROOM);

    gameInfo.setGameId(gameId);
    handlers[0]->doSend(gameInfo.serialize());
}

void ClientNetwork::leaveGame()
{
    SimpleInfo  info(DISCONNECT_GAME);

    handlers[0]->doSend(info.serialize());
}

void ClientNetwork::sendJoystickEvent(const JoystickEvent &event)
{
    handlers[2]->doSend(event.serialize());
}
