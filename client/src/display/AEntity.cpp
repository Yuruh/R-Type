//
// Created by yuruh on 08/12/16.
//

#include <iostream>
#include "display/AEntity.hpp"

AEntity::AEntity(int speed, EntityType name) : speed(speed), x_dir(0), y_dir(0), type(name)
{

}

AEntity::AEntity() : speed(1), x_dir(0), y_dir(0), type(UNDEFINED_ENTITY)
{

}

AEntity::~AEntity()
{

}

void AEntity::setSpeed(int speed)
{
    this->speed = speed;
}

EntityType AEntity::getName() const
{
    return type;
}

void AEntity::setDirection(float x, float y)
{
    this->x_dir = x;
    this->y_dir = y;
}

void AEntity::blink()
{
    ASpritesHandler::setColor(255, 127, 127, 255);
    blinkTime = 0;
    blinking = true;
}

void AEntity::update(float deltaTime)
{
    float offset_x = this->x_dir * deltaTime * speed;
    float offset_y = this->y_dir * deltaTime * speed;

    ASpritesHandler::move(offset_x, offset_y);

    if (blinking)
    {
        blinkTime += deltaTime;
        if (blinkTime > 0.2)
        {
            ASpritesHandler::setColor(255, 255, 255, 255);
            blinking = false;
        }
    }
}

bool AEntity::isDone(int winWidth, int winHeight)
{
    if (this->getPosition().x > winWidth || this->getPosition().x + this->getWidth() < 0)
        return true;
    if (this->getPosition().y > winHeight || this->getPosition().y + this->getHeight() < 0)
        return true;
    return false;
}