//
// Created by ossalag on 14/12/16.
//

#include <Core.hpp>
#include "Game/RType.hpp"
#include "Exception/FactoryException.hpp"

RType::RType(uint32_t id) : AGame(id)
{
    _parser = new RTypeParser(simulator.getChunks());
    try
    {
        _parser->parse("map.xml");
    }
    catch (ParserError const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (FactoryException const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    this->_availableID = std::vector<EntityType>({PLAYER1, PLAYER2, PLAYER3, PLAYER4});
}

RType::~RType()
{
    delete this->_parser;
}

bool RType::isLevelOver() {
    return true;
}

bool RType::isGameOver() {
    return simulator.isEndGame();
}

bool RType::isGameEmpty() {
    return _players.empty();
}

void RType::joystickUsed(float x, float y, uint32_t playerId)
{

}

void RType::startGame() {
    std::cout << "Starting game [" << this->_id << "]" << std::endl;
    simulator.setPlayers(_players);
    this->_isStarted = true;
    for (unsigned int i = 0; i < _players.size(); ++i)
        Core::getInstance().sendGameLaunched(this->_id, _players[i]->getNetworkID());
}

void RType::useButtonEvent(const ButtonEvent &buttonEvent, uint32_t id)
{
    this->simulator.useButtonEvent(buttonEvent, id);
}

void RType::disconnectPlayer(uint32_t playerId)
{
    AGame::disconnectPlayer(playerId);
    this->simulator.disconnectPlayer(playerId);
}

void RType::update(float elapsedTime)
{
    this->simulator.addTime(elapsedTime);
    if (this->simulator.getTick() > TICKRATE)
        simulator.updateAll();
    if (this->simulator.getChunkTime() > CHUNK_LOADING_TIME)
        simulator.updateLiveContent();
}

void RType::useJoystickEvent(const JoystickEvent &event, uint32_t id)
{
    this->simulator.useJoystickEvent(event, id);
}
