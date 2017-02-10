//
// Created by yuruh on 29/12/16.
//

#include <Missiles/WaveMissile.hpp>
#include <Patterns/LinearPattern.hpp>
#include <Game/Simulation/Simulation.hpp>
#include <cmath>
#include <Utils/Convertor.hpp>

WaveMissile::WaveMissile(float x, float y, float xDir, float yDir)
{
    BoundingBox box;

    this->_x = x;
    this->_y = y;
    this->_category = MISSILE_WAVE;
    this->_pattern = new LinearPattern(xDir, yDir);
    this->_speedScale = 0.5;
    box.x = 0;
    box.y = 0;
    box.offsetX = MISSILE_WAVE_SIZE * SERVER_Y / 100;
    box.offsetY = MISSILE_WAVE_SIZE * SERVER_Y / 100;
    this->_boundingBoxes.push_back(box);
}