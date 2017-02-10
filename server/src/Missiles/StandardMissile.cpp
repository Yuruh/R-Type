//
// Created by yuruh on 27/12/16.
//

#include <Game/Simulation/Simulation.hpp>
#include "Missiles/StandardMissile.hpp"

StandardMissile::StandardMissile()
{
    BoundingBox box;

    this->_category = MISSILE;
    this->_pattern = new LinearPattern(1, 0);
    this->_speedScale = 1;
    box.x = 0;
    box.y = 0;
    box.offsetX = MISSILE_SIZE * SERVER_Y / 100;
    box.offsetY = MISSILE_SIZE * SERVER_Y / 100;
    this->_boundingBoxes.push_back(box);
}