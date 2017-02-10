//
// Created by yuruh on 08/12/16.
//

#ifndef RTYPE_IANIMATEDSPRITES_HPP
#define RTYPE_IANIMATEDSPRITES_HPP


#include "IAnimated.hpp"
#include "ASpritesHandler.hpp"

class IAnimatedSprites : public IAnimated, public ASpritesHandler
{
public:
    virtual void    update(float) = 0;
};


#endif //RTYPE_IANIMATEDSPRITES_HPP
