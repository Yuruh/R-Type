//
// Created by ossalag on 17/12/16.
//

#include <Game/Simulation/Simulation.hpp>
#include <Core.hpp>

std::mutex g_mutex;

AGame::AGame(uint32_t id) : _availablesType({PLAYER1, PLAYER2, PLAYER3, PLAYER4})
{
    std::cout << "New Game [" << id << "]" << std::endl;
    this->_id = id;
    this->_isStarted = false;
}

uint32_t AGame::getId() const
{
    return this->_id;
}

bool AGame::isStarted() {
    return  this->_isStarted;
}

const GameList AGame::getRoomInfo() const
{
    GameList    gameList(ROOM_INFO);

    for (unsigned int i = 0; i < this->_players.size(); ++i)
        gameList.gameIDs.push_back(this->_players[i]->getNetworkID());
    return gameList;
}


bool AGame::connectPlayer(uint32_t clientID) {
    if (!this->isStarted() && _players.size() < 4 && !this->_availablesType.empty())
    {
        g_mutex.lock();

        APlayable *player = new Player();
        player->setCategory(this->_availablesType.front());
        player->setNetworkID(clientID);
        this->_availablesType.pop_front();

        unsigned int whichPlayer = static_cast<unsigned int>(player->getCategory()) - 6000;
        player->setX(SERVER_X / 15.0f);
        player->setY(whichPlayer * (SERVER_Y / 5.0f));
        _players.push_back(player);
        Core::getInstance().sendGameInfo(this->getId(), clientID);

        for (unsigned int i = 0; i < this->_players.size(); ++i)
            Core::getInstance().sendRoomInfo(this->_players[i]->getNetworkID());
        g_mutex.unlock();
        return true;
    }
    return false;
}

void AGame::disconnectPlayer(uint32_t playerId)
{
    for (auto it = _players.begin(); it != _players.end();++it)
    {
        if ((*it)->getNetworkID() == playerId)
        {
            this->_availablesType.push_front((*it)->getCategory());
//            delete *it;
			_players.erase(it);
            break;
        }
    }
}

void AGame::leaveRoom(uint32_t playerID)
{
    for (unsigned int i = 0; i < this->_players.size(); ++i)
    {
        if (_players[i]->getNetworkID() == playerID)
        {
            this->_availablesType.push_front(_players[i]->getCategory());
            _players.erase(_players.begin() + i);
            break;
        }
    }
    for (unsigned int i = 0; i < this->_players.size(); ++i)
        Core::getInstance().sendRoomInfo(this->_players[i]->getNetworkID());
}

bool AGame::containPlayer(uint32_t playerId) const
{
    for (unsigned int i = 0; i < this->_players.size(); ++i)
    {
        if (_players[i]->getNetworkID() == playerId)
            return true;
    }
    return false;
}
