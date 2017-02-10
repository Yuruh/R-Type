//
// Created by wasta-geek on 22/12/16.
//

#include <iostream>
#include <vector>
#include <Monsters/Brainfart.hpp>
#include <Game/Simulation/Simulation.hpp>
#include <Utils/Convertor.hpp>
#include "APlayable.hpp"
#include "Missiles/StandardMissile.hpp"

APlayable::APlayable() : AEntity()
{
    this->_dir = {0.0f, 0.0f};
    this->resetEvents();
}

APlayable::~APlayable()
{
}

const std::pair<float, float>& APlayable::getDirection() const
{
    return this->_dir;
}

void APlayable::setPosition(float x, float y)
{
    AEntity::setPosition(x, y);
}

uint32_t APlayable::getHp() const {
    return this->_hp;
}

void APlayable::setHp(uint32_t hp) {
    this->_hp = hp;
}

std::string const &APlayable::getName() const {
    return this->_name;
}

void APlayable::setName(std::string const &name) {
    this->_name = name;
}

void APlayable::takeDmg(uint32_t hp) {
    this->_hp = (this->_hp < hp ? 0 : this->_hp - hp);
    if (this->_hp <= 0)
        this->_dir = std::pair<float, float>(-1.0f, 0.0f);
}

void APlayable::setNetworkID(uint32_t networkID)
{
    this->_networkID = networkID;
}

unsigned int APlayable::getNetworkID() const
{
    return this->_networkID;
}

void APlayable::setEvent(ButtonEvent const &buttonEvent)
{
    this->events[buttonEvent.getButtonType()] = true;
}

void APlayable::resetEvents()
{
    this->events[Z] = false;
    this->events[Q] = false;
    this->events[S] = false;
    this->events[D] = false;
    this->events[UP] = false;
    this->events[DOWN] = false;
    this->events[LEFT] = false;
    this->events[RIGHT] = false;
    this->events[SPACE] = false;
    this->events[RETURN] = false;
    this->joystickX = 0;
    this->joystickY = 0;
}

void APlayable::setEvent(JoystickEvent const &joystickEvent)
{
    this->joystickX = joystickEvent.x;
    this->joystickY = joystickEvent.y;
}
