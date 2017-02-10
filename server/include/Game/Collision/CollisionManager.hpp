//
// Created by ossalag on 11/12/16.
//

#ifndef RTYPE_COLLISIONMANAGER_HPP
#define RTYPE_COLLISIONMANAGER_HPP

#include <vector>
#include "Collision.hpp"
#include "AEntity.hpp"
#include "Player.hpp"
#include "BoundingBox.hpp"

# define DMG    10

class CollisionManager {
public:
    CollisionManager();

    ~CollisionManager();

    uint32_t checkCollision(AEntity const &player, std::vector<ANonPlayable *> const &);

    static bool isCollision(AEntity const *a, AEntity const *b);

};

#endif //RTYPE_COLLISIONMANAGER_HPP
