//
// Created by yuruh on 30/11/16.
//

#include <iostream>
#include "display/SfmlSpriteHandler.hpp"

SfmlSpriteHandler::SfmlSpriteHandler(sf::Texture const& text)
{
    this->sprite.setTexture(text);
}

SfmlSpriteHandler::~SfmlSpriteHandler()
{

}

void  SfmlSpriteHandler::setSize(float width, float height)
{
    auto rect = this->sprite.getGlobalBounds();

    this->sprite.scale(width / rect.width, height / rect.height);
}

void  SfmlSpriteHandler::setProportionalSize(float width, float height)
{
    auto rect = this->sprite.getGlobalBounds();

    float scale = width / rect.width;

    if (height / rect.height > scale)
        scale = height / rect.height;

    this->sprite.scale(scale, scale);
}

void  SfmlSpriteHandler::setPosition(float x, float y)
{
    this->sprite.setPosition(x, y);
}

const sf::Vector2f &SfmlSpriteHandler::getPosition() const
{
    return (this->sprite.getPosition());
}

float SfmlSpriteHandler::getWidth() const
{
    return (this->sprite.getGlobalBounds().width);
}

float SfmlSpriteHandler::getHeight() const
{
    return (this->sprite.getGlobalBounds().height);
}

void  SfmlSpriteHandler::move(float x, float y)
{
    this->sprite.move(x, y);
}

void SfmlSpriteHandler::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->sprite);
}

void SfmlSpriteHandler::setTextureRect(int x, int y, int width, int height)
{
    this->sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void SfmlSpriteHandler::setColor(int r, int g, int b, int a)
{
    this->sprite.setColor(sf::Color(r, g, b, a));
}
