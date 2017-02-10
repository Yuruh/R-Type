//
// Created by ossalag on 10/12/16.
//

#ifndef RTYPE_SIMULATION_HPP
#define RTYPE_SIMULATION_HPP

#include    <vector>
#include    "Timer.hpp"
#include    "IChunk.hpp"
#include    "CollisionManager.hpp"
#include    "EntityPos.hpp"
#include    "ButtonEvent.hpp"
#include    "Missiles/AMissile.hpp"

#define     CHUNK_LOADING_TIME   500
//17 -> 60 refresh par sec
#define     TICKRATE             20

#define     MIN_X          0
#define     MIN_Y          0

#define     SERVER_X       1920
#define     SERVER_Y       1080

class Simulation {
public:
    Simulation();
    Simulation(std::vector<APlayable*> const &players);
    ~Simulation();

    void updateAll();
    void updateLiveContent();
    bool isEndGame();
    void setPlayers(std::vector<APlayable*> const &players);
    bool addTime(float elapsedTime);
    void resetLevel();
    void disconnectPlayer(uint32_t);

    std::vector<IChunk *> &getChunks();

    void useButtonEvent(const ButtonEvent &buttonEvent, uint32_t);
    void useJoystickEvent(const JoystickEvent &event, uint32_t);

    float getTick() const { return (_tick); }
    float getChunkTime() const { return (_chunkTime); }

private:
    void update();

    void updateAlive();

    void fillEntityPacket(AEntity *) const;

private:
    float _tick;
    float _chunkTime;
    CollisionManager _collisionM;
    std::vector<IChunk *> _chunks;
    std::vector<ANonPlayable *> _liveContent;
    std::vector<AMissile *>  _missiles;
    std::vector<APlayable *>  _alivePlayers;
    std::vector<APlayable *>  _deadPlayers;
    bool _hasEnded;

    void sendEntityPos(const AEntity &entity, EntityType entityType, PacketType packetType) const;
};

#endif //RTYPE_SIMULATION_HPP
