//
// Created by ossalag on 15/12/16.
//

#ifndef SERVER_RTYPE_PLAYER_HPP
#define SERVER_RTYPE_PLAYER_HPP

#include <string>
#include "../APlayable.hpp"
#include "../AEntity.hpp"

#define SPAWN_X     10
#define SPAWN_Y     10

#define PLAYER_SPEED 0.6f

#define HP  10

class Player : public APlayable
{
public:
    Player();

    ~Player();

    void update(float deltaTime, std::vector<AMissile *> &missiles);

private:
    float shootCd;
    float waveCd;

    void handleMovement(float deltaTime);
};

#endif //SERVER_RTYPE_PLAYER_HPP
