//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_AANIMATED_HPP
#define RTYPE_AANIMATED_HPP


#include <SFML/Graphics/Drawable.hpp>

class IAnimated : virtual public sf::Drawable
{
public:
    virtual void    update(float) = 0;
};


#endif //RTYPE_AANIMATED_HPP
