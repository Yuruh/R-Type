//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_SCROLLING_HPP
#define RTYPE_SCROLLING_HPP


#include "IAnimatedSprites.hpp"

class Scrolling : public IAnimatedSprites
{
private:
    int           speed;
    int           width;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    Scrolling (sf::Texture const&, sf::Texture const&, int);
    virtual ~Scrolling ();
    virtual void update(float);

    void setSize(float width, float height);

    void setPosition(float x, float y);
};


#endif //RTYPE_SCROLLING_HPP
