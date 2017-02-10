//
// Created by yuruh on 01/12/16.
//

#ifndef RTYPE_MULTISPRITE_HPP
#define RTYPE_MULTISPRITE_HPP


#include "AEntity.hpp"

class TileSetSprites : public AEntity
{
public:
    TileSetSprites(EntityType entityName);
private:
    unsigned int             counter;
    float           t;
    float           refreshRate;
    bool            repeat;

public:
    TileSetSprites(const sf::Texture &tileset, sf::IntRect rect, int qty, float, bool);
    ~TileSetSprites();
    void    draw(sf::RenderTarget &, sf::RenderStates) const;
    void    addSprites(const sf::Texture &tileset, sf::IntRect rect, int qty);
    virtual void    update(float);
    bool    isDone(int winWidth, int winHeight);

    void reset();
};


#endif //RTYPE_MULTISPRITE_HPP
