//
// Created by wasta-geek on 22/12/16.
//

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <Utils/Convertor.hpp>
#include "SinusoidalePattern.hpp"

SinusoidalePattern::SinusoidalePattern(float x)
{
    this->_type = Pattern::Sinusoidale;
    this->ticks = 0;
    this->x = x;
    // 17 == TICKRATE
    this->_dir = std::pair<float, float>(this->x, (float)sin(ticks * 0.5f * M_PI));
}

SinusoidalePattern::~SinusoidalePattern() {}

void    SinusoidalePattern::update()
{
    float y = (float) sin(ticks * 0.02 * M_PI);
    this->ticks++;
    Convertor::normalizeVector(this->x, y);
    this->_dir = std::pair<float, float>(this->x, y);
}
