//
// Created by wasta-geek on 06/12/16.
//

#include "APattern.hpp"

APattern::~APattern() {}

Pattern::type APattern::getType() const
{
    return this->_type;
}

std::pair<float, float> const &APattern::getDirection() const
{
    return this->_dir;
}
