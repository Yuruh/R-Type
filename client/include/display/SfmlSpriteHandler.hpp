//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_ASPRITEHANDLER_HPP
#define RTYPE_ASPRITEHANDLER_HPP

#include <SFML/Graphics.hpp>

class SfmlSpriteHandler : public sf::Drawable
{
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
protected:
    sf::Sprite    sprite;
public:
    SfmlSpriteHandler (sf::Texture const&);
    virtual ~SfmlSpriteHandler ();
    void setPosition(float, float);
    const sf::Vector2f &getPosition() const;
    float   getWidth() const;
    float   getHeight() const;
    void move(float, float);
    void setSize(float, float);
    void setTextureRect(int x, int y, int width, int height);
    void setColor(int r, int g, int b, int a);

    void setProportionalSize(float width, float height);
};

#endif //RTYPE_ASPRITEHANDLER_HPP
