//
// Created by ossalag on 11/12/16.
//

#include <iostream>
#include <Entities/ANonPlayable.hpp>
#include "CollisionManager.hpp"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{

}

uint32_t CollisionManager::checkCollision(AEntity const &player, std::vector<ANonPlayable *> const &entities)
{
    for (auto entityIt = entities.begin(); entityIt != entities.end(); ++entityIt)
        if (isCollision(&player, *entityIt))
            return DMG;
    return 0;
}

bool CollisionManager::isCollision(AEntity const *a, AEntity const *b)
{
    const std::vector<BoundingBox> &boxA = a->getBoundingBoxes();
    const std::vector<BoundingBox> &boxB = b->getBoundingBoxes();

    if (boxA.empty() || boxB.empty())
        return false;

    float xA = a->getX() + boxA[0].x + boxA[0].offsetX / 2;
    float yA = a->getY() + boxA[0].y + boxA[0].offsetY / 2;


    float xB = b->getX() + boxB[0].x + boxB[0].offsetX / 2;
    float yB = b->getY() + boxB[0].y + boxB[0].offsetY / 2;

    return (abs((int) (xA - xB)) * 2 < boxA[0].offsetX + boxB[0].offsetX &&
            abs((int) (yA - yB)) * 2 < boxA[0].offsetY + boxB[0].offsetY);
}