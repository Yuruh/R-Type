//
// ServerNetwork.hpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/server/src/Network/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Wed Dec  7 15:12:09 2016 Raphael Thiebault
// Last update Sun Dec 18 12:58:43 2016 Raphael Thiebault
//

#pragma once

#include	<vector>
#include <Serializable/EntityPos.hpp>
#include	"Network/INetwork.hpp"
#include	"ThreadPool.hpp"
#include	"TcpSocket.hpp"
#include	"UdpSocket.hpp"

class ServerNetwork : public INetwork {
protected:
    std::map<int, ISocket*>	                in_game;
    std::map<int, ISocket*>	                connected;
    std::map<std::vector<uint32_t>, uint32_t >    address_book;

    std::vector<ISocket *>      handlers;
    std::vector<struct pollfd>  fds;
    ThreadPool         pool;

    int                         clientId = 1;

private:
    ISocket*    addConnection(ISocket *socket);
    void        removeConnection(int clientId);
    ISocket     *addHandler(ISocket *socket);

public:
    ServerNetwork(uint16_t port = 4242, bool ssl = false);
    ~ServerNetwork();

    void    run();
    void    clientConnected(uint32_t clientId, uint16_t port);
    void    clientRegistered(uint32_t clientId, uint16_t port);
    void    sendEntityPos(uint32_t id, const EntityPos &pos);
    void    sendGameList(uint32_t id, const GameList&);
    void    sendGameInfo(uint32_t gameId, uint32_t playerId);
    void    sendGameLaunched(uint32_t gameId, uint32_t playerId);
    void    sendEndGame(bool, uint32_t);
};
