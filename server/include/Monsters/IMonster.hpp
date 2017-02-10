//
// Created by wasta-geek on 06/12/16.
//

#ifndef SHARED_IMONSTER_HPP
#define SHARED_IMONSTER_HPP

#include <Entities/ANonPlayable.hpp>

class IMonster : public ANonPlayable {
public:
    virtual void takeDamage(const int &) = 0;

    virtual void kill() = 0;

    virtual ~IMonster() {};
};

#endif //SHARED_IMONSTER_HPP
