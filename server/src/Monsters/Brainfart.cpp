//
// Created by wasta-geek on 08/12/16.
//

#include <iostream>
#include <Game/Simulation/Simulation.hpp>
#include <Utils/Convertor.hpp>
#include "Monsters/Brainfart.hpp"
#include "Patterns/LinearPattern.hpp"

Brainfart::Brainfart() : AMonster()
{
    BoundingBox box;

    this->_category = BRAINFART;
    this->_pattern = new LinearPattern();

    box.x = 0;
    box.y = 0;
    box.offsetX =  BRAINFART_SIZE * SERVER_Y / 100;
    box.offsetY =  BRAINFART_SIZE * 2 * SERVER_Y / 100;

    this->_boundingBoxes.push_back(box);
}

Brainfart::~Brainfart()
{
}
