//
// Created by yuruh on 26/12/16.
//

#include <Patterns/LinearPattern.hpp>
#include <Game/Simulation/Simulation.hpp>
#include "Monsters/Taz.hpp"

Taz::Taz()
{
    BoundingBox box;

    this->_category = TAZ;
    this->_pattern = new LinearPattern(-1, 0);
    box.x = 0;
    box.y = 0;
    box.offsetX = TAZ_SIZE * SERVER_Y / 100;
    box.offsetY = TAZ_SIZE * SERVER_Y / 100;
    this->_boundingBoxes.push_back(box);
}

Taz::~Taz()
{

}