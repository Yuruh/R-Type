//
// Created by yuruh on 02/12/16.
//

#include "display/ASpritesHandler.hpp"

ASpritesHandler::ASpritesHandler() : mainPos(0, 0)
{

}

ASpritesHandler::~ASpritesHandler()
{

}

void ASpritesHandler::setPosition(float x, float y)
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->sprites[i].setPosition(x, y);
    this->mainPos = this->getPosition();
}

const sf::Vector2f &ASpritesHandler::getPosition() const
{
    if (this->sprites.size() > 0)
        return this->sprites[0].getPosition();
    return (this->mainPos);
}

void    ASpritesHandler::setProportionalSize(float width, float height)
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->sprites[i].setProportionalSize(width, height);
}

float ASpritesHandler::getWidth() const
{
    if (this->sprites.size() > 0)
        return this->sprites[0].getWidth();
    return (0);
}

float ASpritesHandler::getHeight() const
{
    if (this->sprites.size() > 0)
        return this->sprites[0].getHeight();
    return (0);
}

void ASpritesHandler::move(float x, float y)
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->sprites[i].move(x, y);
}

void ASpritesHandler::setSize(float width, float height)
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->sprites[i].setSize(width, height);
}

void ASpritesHandler::setColor(int r, int g, int b, int a)
{
    for (unsigned int i = 0; i < this->sprites.size(); ++i)
        this->sprites[i].setColor(r, g, b, a);
}
