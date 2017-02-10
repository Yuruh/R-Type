//
// Created by wasta-geek on 22/12/16.
//

#ifndef SERVER_RTYPE_SINUSOIDALE_HPP
#define SERVER_RTYPE_SINUSOIDALE_HPP

#include "APattern.hpp"

class SinusoidalePattern : public APattern
{
private:
    unsigned int    ticks;
    float						x;
public:
    SinusoidalePattern(float x = -1);
    ~SinusoidalePattern();

    void update();
};


#endif //SERVER_RTYPE_SINUSOIDALE_HPP
