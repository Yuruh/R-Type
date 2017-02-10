//
// Created by ossalag on 11/12/16.
//

#ifndef SERVER_RTYPE_COLLISION_HPP
#define SERVER_RTYPE_COLLISION_HPP

#include <utility>
#include <map>

class Collision {
public:
    Collision();

    ~Collision();

    uint32_t getPlayerId() const;

    void setPlayerId(uint32_t playerId);

    std::pair<float, float> const &getPlayerPos() const;

    void setPlayerPos(float x, float y);

    void setPlayerPos(std::pair<float, float> playerPos);

    std::pair<uint32_t, uint32_t> const &getEntityId() const;

    void setEntityId(uint32_t type, uint32_t id);

    void setEntityId(std::pair<uint32_t, uint32_t> entityId);

    std::pair<float, float> getEntityPos() const;

    void setEntityPos(float x, float y);

    void setEntityPos(std::pair<float, float> entityPos);

private:
    uint32_t _playerId;
    std::pair<float, float> _playerPos;
    std::pair<uint32_t, uint32_t> _entityId;
    std::pair<float, float> _entityPos;
};

#endif //SERVER_RTYPE_COLLISION_HPP
