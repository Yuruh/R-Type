//
// Created by yuruh on 29/12/16.
//

#ifndef CLIENT_RTYPE_PLAYERSPRITES_HPP
#define CLIENT_RTYPE_PLAYERSPRITES_HPP

#include <display/AEntity.hpp>

class PlayerSprites : public AEntity
{
public:
    PlayerSprites(EntityType entityName);
    ~PlayerSprites();
    virtual void    update(float);

private:
    unsigned int    counter;
    float           t;
    float           refreshRate;
    bool            repeat;

    void addSprites(const sf::Texture &tileset, sf::IntRect rect, int qty);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void reset();
};


#endif //CLIENT_RTYPE_PLAYERSPRITES_HPP
