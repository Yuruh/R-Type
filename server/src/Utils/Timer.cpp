//
// Created by ossalag on 10/12/16.
//

#include <iostream>
#include    "Timer.hpp"

Timer::Timer() {

}

Timer::~Timer() {

}

void Timer::start() {
    _startTime = std::chrono::steady_clock::now();
}

float Timer::timeSinceLastUpdate()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<float> duration = now - _startTime;

    _startTime = now;
    
    return duration.count() * 1000;
}
