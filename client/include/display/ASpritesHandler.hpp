//
// Created by yuruh on 02/12/16.
//

#ifndef RTYPE_ASPRITESHANDLER_HPP
#define RTYPE_ASPRITESHANDLER_HPP


#include <SFML/Graphics/Drawable.hpp>
#include "SfmlSpriteHandler.hpp"

class ASpritesHandler : virtual public sf::Drawable
{
protected:
    std::vector<SfmlSpriteHandler>  sprites;
    sf::Vector2f                    mainPos;
public:
    ASpritesHandler();
    ~ASpritesHandler();
    virtual void setPosition(float, float);
    virtual const sf::Vector2f &getPosition() const;
    float   getWidth() const;
    float   getHeight() const;
    virtual void move(float, float);
    virtual void setSize(float, float);
    virtual void setColor(int r, int g, int b, int a);

    void setProportionalSize(float width, float height);
};


#endif //RTYPE_ASPRITESHANDLER_HPP
