//
// Created by wasta-geek on 13/12/16.
//

#ifndef SERVER_RTYPE_LINEARPATTERN_HPP
#define SERVER_RTYPE_LINEARPATTERN_HPP

#include "APattern.hpp"

class LinearPattern : public APattern
{
public:
    LinearPattern(float x = -1, float y = 0);
    ~LinearPattern();
};


#endif //SERVER_RTYPE_LINEARPATTERN_HPP
