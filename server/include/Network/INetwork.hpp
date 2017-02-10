//
// INetwork.hpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/server/src/Network/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Wed Dec  7 13:35:51 2016 Raphael Thiebault
// Last update Sun Dec 11 22:11:36 2016 Raphael Thiebault
//

#pragma once

#include	<vector>
#include	"Threadable.hpp"
#include    "GameList.hpp"

class INetwork : public Threadable {
public:
    virtual void clientConnected(uint32_t clientId, uint16_t port) = 0;

    virtual void clientRegistered(uint32_t clientId, uint16_t port) = 0;

    virtual void    sendEntityPos(uint32_t playerId, const EntityPos &pos) = 0;

    virtual void    sendGameList(uint32_t id, const GameList&)= 0;

    virtual void sendGameInfo(uint32_t gameId, uint32_t) =0;

    virtual void sendGameLaunched(uint32_t gameId, uint32_t)= 0;

    virtual void sendEndGame(bool, uint32_t) = 0;
};
