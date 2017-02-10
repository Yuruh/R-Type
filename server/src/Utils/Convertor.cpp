//
// Created by ossalag on 13/12/16.
//

#include <Game/Simulation/Simulation.hpp>
#include <math.h>
#include "Convertor.hpp"

Convertor::Convertor() {

}

Convertor::~Convertor() {

}

void Convertor::normalizeVector(float &x, float &y)
{
    float length = (float) sqrt((x * x) + (y * y));

    x = x / length;
    y = y / length;
}

float Convertor::toRelativeClient(float const i, char const flag) {
    float res;
    if (flag == 'x') {
        res = PERCENT(i) * RES_CLIENT(SERVER_X) + (ZOOM / 4);
    } else {
        res = PERCENT(i) * RES_CLIENT(SERVER_Y) + (ZOOM / 4);
    }
    return res;
}

float Convertor::toRelativeServer(float const i, char const flag) {
    float res;
    if (flag == 'x') {
        res = PERCENT(i) * SERVER_X;
    } else {
        res = PERCENT(i) * SERVER_Y;
    }
    return res;
}

float Convertor::toPercentClient(float const i, char const flag) {
    float res;
    if (flag == 'x') {
        res = (i - ZOOM / 4) / (SERVER_X - (SERVER_X * (ZOOM / 100))) * 100;
    } else {
        res = (i - ZOOM / 4) / (SERVER_Y - (SERVER_Y * (ZOOM / 100))) * 100;
    }
    return res;
}

float Convertor::toPercentServer(float const i, char const flag) {
    float res;
    if (flag == 'x') {
        res = i / SERVER_X * 100;
    } else {
        res = i / SERVER_Y * 100;
    }
    return res;
}