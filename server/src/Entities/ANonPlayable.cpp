//
// Created by wasta-geek on 22/12/16.
//

#include "ANonPlayable.hpp"
#include "SinusoidalePattern.hpp"
#include "LinearPattern.hpp"

ANonPlayable::ANonPlayable()
{
  this->_pattern = nullptr;
}

ANonPlayable::~ANonPlayable()
{
    delete this->_pattern;
}

Pattern::type ANonPlayable::getPattern() const
{
    return this->_pattern->getType();
}

void ANonPlayable::updatePattern()
{
    this->_pattern->update();
}

void ANonPlayable::setPattern(Pattern::type patternType) {
    delete this->_pattern;
    switch (patternType) {
        case Pattern::Linear:
            this->_pattern = new LinearPattern(-1, 0);
            break;
        case Pattern::Sinusoidale:
            this->_pattern = new SinusoidalePattern(-1);
            break;
        case Pattern::TopLeft:
            this->_pattern = new LinearPattern(-1, -0.5);
            break;
        case Pattern::BottomLeft:
            this->_pattern = new LinearPattern(-1, 0.5);
            break;
        case Pattern::TopBottom:
            this->_pattern = new LinearPattern(0, -1);
            break;
        case Pattern::BottomTop:
            this->_pattern = new LinearPattern(0, 1);
            break;
        case Pattern::InverseLinear:
            this->_pattern = new LinearPattern(1, 0);
            break;
        case Pattern::InverseSinusoidale:
            this->_pattern = new SinusoidalePattern(1);
            break;
        default:
            this->_pattern = new LinearPattern(-1, 0);
            break;
    }
}

const std::pair<float, float> &ANonPlayable::getDirection() const
{
    return this->_pattern->getDirection();
}
