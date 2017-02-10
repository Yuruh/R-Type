//
// Created by ossalag on 10/12/16.
//

#include <iostream>
#include <Core.hpp>
#include <Serializable/SimpleInfo.hpp>
#include "Simulation.hpp"
#include "Convertor.hpp"

//TODO : POOL D'OBJET

Simulation::Simulation()
{
    this->_chunkTime = 0;
    this->_tick = 0;
    this->_hasEnded = false;
}

Simulation::Simulation(std::vector<APlayable*> const &players)
{
    setPlayers(players);
}

Simulation::~Simulation()
{
    g_mutex.lock();
    for (unsigned int i = 0; i < this->_missiles.size(); ++i)
        delete this->_missiles[i];
    for (unsigned int i = 0; i < this->_liveContent.size(); ++i)
        delete this->_liveContent[i];
    g_mutex.unlock();
}

bool Simulation::isEndGame()
{
    return (_chunks.empty() && _liveContent.empty()) || this->_alivePlayers.empty();
}

bool Simulation::addTime(float elapsedTime)
{
    if (this->_hasEnded)
        return (false);
    this->_chunkTime += elapsedTime;
    this->_tick += elapsedTime;
    return (true);
}

void Simulation::updateAll()
{
    g_mutex.lock();
    for (auto it = this->_alivePlayers.begin(); it != this->_alivePlayers.end(); ++it)
        (*it)->update(_tick, _missiles);
    g_mutex.unlock();
    update();
}

void Simulation::sendEntityPos(AEntity const &entity, EntityType entityType, PacketType packetType) const
{
    EntityPos   pos(packetType);

    pos.idDesc = entityType;
    pos.idGen = entity.getId();
    pos.x = Convertor::toPercentClient(entity.getX(), 'x');
    pos.y = Convertor::toPercentClient(entity.getY(), 'y');
    pos.xDir = entity.getDirection().first * entity.getSpeedScale() * this->_tick;
    pos.yDir = entity.getDirection().second * entity.getSpeedScale() * this->_tick;
    pos.firstPlan = entity.isFirstPlan();
    for (unsigned int i = 0; i < this->_alivePlayers.size(); ++i)
        Core::getInstance().sendEntityPositions(this->_alivePlayers[i]->getNetworkID(), pos);
    for (unsigned int i = 0; i < this->_deadPlayers.size(); ++i)
        Core::getInstance().sendEntityPositions(this->_deadPlayers[i]->getNetworkID(), pos);
}

void Simulation::update()
{
    if (this->isEndGame() && !this->_hasEnded)
    {
        bool isVictory = true;
        if (this->_alivePlayers.size() == 0)
            isVictory = false;
        for (unsigned int i = 0; i < _alivePlayers.size(); ++i)
            Core::getInstance().sendEndGame(isVictory, _alivePlayers[i]->getNetworkID());
        for (unsigned int i = 0; i < _deadPlayers.size(); ++i)
            Core::getInstance().sendEndGame(isVictory, _deadPlayers[i]->getNetworkID());
        this->_hasEnded = true;
        return;
    }
    size_t size = _liveContent.size();
    for (unsigned int i = 0; i < size; ++i)
    {
        fillEntityPacket(_liveContent[i]);
        _liveContent[i]->updatePattern();
    }

    if (!g_mutex.try_lock())
        return;
    for (auto it = _alivePlayers.begin(); it != _alivePlayers.end(); ++it)
    {
        this->sendEntityPos(*(*it), (*it)->getCategory(), ENTITY_POS);
        uint32_t dmg = _collisionM.checkCollision(*(*it), _liveContent);
        if (dmg)
            (*it)->takeDmg(dmg);
    }
    g_mutex.unlock();

    if (!_missiles.empty())
    {
		size = _missiles.size();
		for (unsigned int i = 0; i < size; ++i)
			fillEntityPacket(_missiles[i]);

		for (auto it_live = _liveContent.begin(); it_live != _liveContent.end(); it_live++)
		{
			for (auto it_missiles = _missiles.begin(); it_missiles != _missiles.end(); ++it_missiles)
			{
				if (CollisionManager::isCollision(*it_live, *it_missiles))
				{
					this->sendEntityPos(*(*it_live), EXPLOSION, DEATH_ENTITY);
					this->sendEntityPos(*(*it_missiles), SILENT_DEATH, DEATH_ENTITY);

					delete *it_live;
					delete *it_missiles;
					it_live = _liveContent.erase(it_live);
					it_missiles = _missiles.erase(it_missiles);
					break;
				}
			}
			if (it_live == _liveContent.end())
				break;
		}
	}
	updateAlive();
	this->_tick = 0;
}
void Simulation::fillEntityPacket(AEntity *entity) const
{
	this->sendEntityPos(*entity, entity->getCategory(), ENTITY_POS);

	float x = entity->getDirection().first * entity->getSpeedScale() * this->_tick;
	float y = entity->getDirection().second * entity->getSpeedScale() * this->_tick;


	entity->setPosition(entity->getX() + x, entity->getY() + y);
}

void Simulation::updateLiveContent()
{
	_chunkTime = 0;
	if (!this->_chunks.empty())
	{
		std::vector<ANonPlayable *> tmp = _chunks.front()->getContents();
		if (_liveContent.empty()) {
			_liveContent = tmp;
		}
		else {
			_liveContent.insert(_liveContent.end(), tmp.begin(), tmp.end());
		}
		delete *(_chunks.begin());
        _chunks.erase(_chunks.begin());
    }
}

void Simulation::updateAlive()
{
    for (auto it = _liveContent.begin(); it != _liveContent.end();) {
        if ((*it)->getX() < MIN_X - (*it)->getBoundingBoxes()[0].offsetX - SPAWN_ZONE
            || (*it)->getY() < MIN_Y - (*it)->getBoundingBoxes()[0].offsetY - SPAWN_ZONE ||
            (*it)->getX() > SERVER_X + SPAWN_ZONE || (*it)->getY() > SERVER_Y + SPAWN_ZONE)
        {
            delete *it;
            it = _liveContent.erase(it);
        }
        else
            ++it;
    }
    for (auto it = _missiles.begin(); it != _missiles.end();) {
        if ((*it)->getX() < MIN_X - (*it)->getBoundingBoxes()[0].offsetX ||
                (*it)->getY() < MIN_Y - (*it)->getBoundingBoxes()[0].offsetY ||
            (*it)->getX() > SERVER_X || (*it)->getY() > SERVER_Y)
        {
            delete *it;
            it = _missiles.erase(it);
        }
        else
            ++it;
    }
    for (auto it = _alivePlayers.begin(); it != _alivePlayers.end();) {
        if (!(*it)->getHp())
        {
            APlayable *deadPlayer = *it;

            this->sendEntityPos(*(*it), EXPLOSION, DEATH_ENTITY);
            std::cout << " A PLAYER IS DEAD" << std::endl;
            _deadPlayers.push_back(deadPlayer);
			it = _alivePlayers.erase(it);
        }
        else
            ++it;
    }
};

void Simulation::resetLevel()
{
    _deadPlayers.clear();
}

std::vector<IChunk *> &Simulation::getChunks()
{
    return this->_chunks;
}

void Simulation::setPlayers(std::vector<APlayable*> const &players)
{
    for (unsigned int i = 0; i < players.size(); ++i)
    {
        _alivePlayers.push_back(players[i]);
    }
}

void Simulation::useButtonEvent(const ButtonEvent &buttonEvent, uint32_t id)
{
    for (unsigned int i = 0; i < this->_alivePlayers.size(); ++i)
        if (this->_alivePlayers[i]->getNetworkID() == id)
        {
            this->_alivePlayers[i]->setEvent(buttonEvent);
            break;
        }
}

void Simulation::disconnectPlayer(uint32_t playerId)
{
    g_mutex.lock();
    for (auto it = _alivePlayers.begin(); it != _alivePlayers.end();it++)
    {
        if ((*it)->getNetworkID() == playerId)
        {
            this->sendEntityPos(*(*it), EXPLOSION, DEATH_ENTITY);
            _alivePlayers.erase(it);
            g_mutex.unlock();
            return;
        }
    }
    for (auto it = _deadPlayers.begin(); it != _deadPlayers.end();it++)
    {
        if ((*it)->getNetworkID() == playerId)
        {
            _deadPlayers.erase(it);
            g_mutex.unlock();
            return;
        }
    }
    g_mutex.unlock();
}

void Simulation::useJoystickEvent(const JoystickEvent &joystickEvent, uint32_t id)
{
    for (unsigned int i = 0; i < this->_alivePlayers.size(); ++i)
        if (this->_alivePlayers[i]->getNetworkID() == id)
        {
            this->_alivePlayers[i]->setEvent(joystickEvent);
            break;
        }
}
