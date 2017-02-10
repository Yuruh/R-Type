//
// Created by yuruh on 26/12/16.
//

#include <Patterns/LinearPattern.hpp>
#include <Game/Simulation/Simulation.hpp>
#include "EnemyShip.hpp"

EnemyShip::EnemyShip()
{
    BoundingBox box;

    this->_category = ENEMY_SHIP;
    this->_pattern = new LinearPattern(-1, 0);
    box.x = 0;
    box.y = 0;
    box.offsetX = ENNEMY_SIZE * SERVER_Y / 100;
    box.offsetY = ENNEMY_SIZE * SERVER_Y / 100;
    this->_boundingBoxes.push_back(box);
}

EnemyShip::~EnemyShip()
{
}
