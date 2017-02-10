//
// Created by yuruh on 29/12/16.
//

#ifndef SERVER_RTYPE_WAVEMISSILE_HPP_HPP
#define SERVER_RTYPE_WAVEMISSILE_HPP_HPP

#include "AMissile.hpp"

class WaveMissile : public AMissile
{
public:
    WaveMissile(float, float, float, float);

    ~WaveMissile()
    {

    }
};

#endif //SERVER_RTYPE_WAVEMISSILE_HPP_HPP
