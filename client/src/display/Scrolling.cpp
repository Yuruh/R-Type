//
// Created by yuruh on 30/11/16.
//

#include <iostream>
#include "display/Scrolling.hpp"

Scrolling::Scrolling(sf::Texture const& text1, sf::Texture const& text2, int speed)
{
    this->sprites.push_back(SfmlSpriteHandler(text1));
    this->sprites.push_back(SfmlSpriteHandler(text2));
    this->speed = speed;
    this->width = (int) this->sprites[1].getWidth();
    this->sprites[1].setPosition(this->width, 0.0f);
}

Scrolling::~Scrolling()
{

}

void    Scrolling::update(float timeSinceLastFrame)
{
    this->sprites[0].move(-this->speed * timeSinceLastFrame, 0.f);
    this->sprites[1].move(-this->speed * timeSinceLastFrame, 0.f);
    if (this->sprites[1].getPosition().x  < -this->width + 1)
        this->sprites[1].setPosition(this->width, 0.0f);
    if (this->sprites[0].getPosition().x  < -this->width + 1)
        this->sprites[0].setPosition(this->width, 0.0f);
}

void    Scrolling::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(this->sprites[0]);
    target.draw(this->sprites[1]);
}

void    Scrolling::setSize(float width, float height)
{
    ASpritesHandler::setSize(width, height);

    this->width = (int) this->sprites[1].getWidth();
    this->sprites[1].setPosition(this->width, 0.0f);
}

void    Scrolling::setPosition(float x, float y)
{
    ASpritesHandler::setPosition(x, y);
    this->sprites[1].setPosition(x - this->width, 0.0f);
}