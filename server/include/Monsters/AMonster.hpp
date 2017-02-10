//
// Created by wasta-geek on 06/12/16.
//

#ifndef SHARED_AMONSTER_HPP
#define SHARED_AMONSTER_HPP


#include "IMonster.hpp"

class AMonster : public IMonster {
protected:
    unsigned int _hp;
public:
    AMonster();

    virtual ~AMonster();

    void takeDamage(const int &i);

    void kill();
};


#endif //SHARED_AMONSTER_HPP
