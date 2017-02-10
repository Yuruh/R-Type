//
// Runnable.hpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/shared/include/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Sun Dec 11 21:55:20 2016 Raphael Thiebault
// Last update Sun Dec 11 22:51:58 2016 Raphael Thiebault
//

#pragma once

#include	<thread>
#include	<mutex>

class	Threadable
{
protected:
    bool		running;

public:

    void	start()
    {
        running = true;
        std::thread mainThread = std::thread(&Threadable::run, this);// MAKE IT ABSTRACT HERE
        mainThread.detach();
    }

    virtual void	run() = 0;

    void	stop()
    {
        std::mutex mainMutex; // MAKE IT ABSTRACT HERE
        mainMutex.lock();
        running = false;
        mainMutex.unlock();
    }
};
