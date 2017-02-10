//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_SELECTABLE_HPP
#define RTYPE_SELECTABLE_HPP

#include <iostream>

#include "SfmlSpriteHandler.hpp"
#include "ASpritesHandler.hpp"

#define SELETECTED_MIN_TIME 0.2

class Selectable : public ASpritesHandler
{
protected:
    bool  selected;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
    float t;
public:
    Selectable(sf::Texture const&, sf::Texture const&);
    virtual ~Selectable ();

    void    addTime(float);
    bool    isReady() const;

    inline bool isActive() { return (selected); };
    void setSelected(bool isSelected);
};


#endif //RTYPE_SELECTABLE_HPP
