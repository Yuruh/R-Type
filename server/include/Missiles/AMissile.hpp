//
// Created by yuruh on 27/12/16.
//

#ifndef SERVER_RTYPE_AMISSILE_HPP
#define SERVER_RTYPE_AMISSILE_HPP


#include <Entities/ANonPlayable.hpp>

class AMissile : public ANonPlayable
{
protected:
    unsigned int _dmg;
public:
    AMissile();
    ~AMissile();
};


#endif //SERVER_RTYPE_AMISSILE_HPP
