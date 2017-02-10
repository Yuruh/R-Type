//
// Created by wasta-geek on 13/12/16.
//

#include <Utils/Convertor.hpp>
#include "Patterns/LinearPattern.hpp"

LinearPattern::~LinearPattern() {}


LinearPattern::LinearPattern(float x, float y)
{
    Convertor::normalizeVector(x, y);
    this->_type = Pattern::Linear;
    this->_dir = std::pair<float, float>(x, y);
}
