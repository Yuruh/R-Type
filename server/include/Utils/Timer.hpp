//
// Created by ossalag on 10/12/16.
//

#ifndef RTYPE_TIMER_HPP
#define RTYPE_TIMER_HPP

#include <chrono>

class Timer {
public:
    Timer();

    ~Timer();

    void start();

//    return time as Milliseconds
    float timeSinceLastUpdate();

private:
    std::chrono::steady_clock::time_point _startTime;
    int _elapsedTime;
};

#endif //RTYPE_TIMER_HPP
