//
// Created by wasta-geek on 14/12/16.
//

#include <Core.hpp>
#include "Game/RType.hpp"
#include "Game/GameManager.hpp"

uint32_t  GameManager::_gameId = 0;

std::mutex gameManagerMutex;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
    for (unsigned int i = 0; i < _games.size(); ++i)
        delete _games[i];
    _games.clear();
}

void GameManager::run() {
    _timer.start();
    while (running) {
        if (!_games.empty())
           updateGames();
    }
}

bool GameManager::joinGame(uint32_t playerId, uint32_t gameID)
{
    for (auto it = _games.begin(); it != _games.end(); ++it) {
        if ((*it)->getId() == gameID && !(*it)->containPlayer(playerId)) {
            _players[playerId] = (*it);
            return (*it)->connectPlayer(playerId);
        }
    }
    return false;
}

void GameManager::launchGame(uint32_t gameID)
{
    for (auto it = _games.begin(); it != _games.end(); ++it) {
        if ((*it)->getId() == gameID) {
            if (!(*it)->isStarted())
                (*it)->startGame();
            else
                std::cerr << "Game already started" << std::endl;
            break;
        }
    }
}

void GameManager::quitGame(uint32_t playerId, uint32_t gameID)
{
    for (auto it = _games.begin(); it != _games.end(); ++it) {
        if ((*it)->getId() == gameID) {
            (*it)->disconnectPlayer(playerId);
            break;
        }
    }
}

void GameManager::createGame(uint32_t clientId)
{
    gameManagerMutex.lock();
    AGame   *game = new RType(_gameId++);
    game->connectPlayer(clientId);
    _games.push_back(game);
    this->_players[clientId] = game;
    gameManagerMutex.unlock();
    Core::getInstance().sendGameInfo(game->getId(), clientId);
}

void GameManager::useButtonEvent(uint32_t playerId, const ButtonEvent &buttonEvent)
{
    if (this->_players.find(playerId) != this->_players.end())
        this->_players[playerId]->useButtonEvent(buttonEvent, playerId);
}

void GameManager::useJoystickEvent(uint32_t playerId, const JoystickEvent &event)
{
    if (this->_players.find(playerId) != this->_players.end())
        this->_players[playerId]->useJoystickEvent(event, playerId);
}

void GameManager::updateGames() {
    gameManagerMutex.lock();
    float time = _timer.timeSinceLastUpdate();
    size_t size = _games.size();
    for (unsigned int i = 0; i < size; ++i) {
        if (_games[i]->isStarted()) {
            _games[i]->update(time);
        }
    }
    gameManagerMutex.unlock();
}

const GameList GameManager::getGameList() const
{
    GameList    gameList(GAME_LIST);

    for (unsigned int i = 0; i < this->_games.size(); ++i)
        if (!this->_games[i]->isStarted())
            gameList.gameIDs.push_back(this->_games[i]->getId());
    return gameList;
}

const GameList GameManager::getRoomInfo(uint32_t playerId)
{
    GameList    gameList(ROOM_INFO);

    if (this->_players.find(playerId) != this->_players.end())
        return this->_players[playerId]->getRoomInfo();
    return gameList;
}

void GameManager::notifyLeaveRoom(uint32_t playerId, uint32_t gameID)
{
    for (auto it = _games.begin(); it != _games.end(); ++it) {
        if ((*it)->getId() == gameID) {
            (*it)->leaveRoom(playerId);
            break;
        }
    }
}

void GameManager::useLeaveGame(uint32_t playerId)
{
    if (this->_players.find(playerId) != this->_players.end())
        this->_players[playerId]->disconnectPlayer(playerId);
}
