//
// Created by yuruh on 30/11/16.
//

#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <Core.hpp>
#include "EventsSfml.hpp"

EventsSfml::EventsSfml()
{
    _buttonPressed[sf::Keyboard::Unknown] = UNKNOWN_BUTTON;
    _buttonPressed[sf::Keyboard::Space] = SPACE;
    _buttonPressed[sf::Keyboard::Escape] = ESCAPE;
    _buttonPressed[sf::Keyboard::Return] = RETURN;
    _buttonPressed[sf::Keyboard::BackSpace] = BACKSPACE;
    _buttonPressed[sf::Keyboard::Z] = Z;
    _buttonPressed[sf::Keyboard::Up] = UP;
    _buttonPressed[sf::Keyboard::Q] = Q;
    _buttonPressed[sf::Keyboard::Down] = DOWN;
    _buttonPressed[sf::Keyboard::S] = S;
    _buttonPressed[sf::Keyboard::Left] = LEFT;
    _buttonPressed[sf::Keyboard::D] = D;
    _buttonPressed[sf::Keyboard::Right] = RIGHT;

    _joystickButtonPressed[0] = DOWN;
    _joystickButtonPressed[1] = RIGHT;
    _joystickButtonPressed[2] = LEFT;
    _joystickButtonPressed[3] = UP;
    _joystickButtonPressed[4] = SPACE;
    _joystickButtonPressed[5] = RETURN;
    _joystickButtonPressed[6] = ESCAPE;


    this->clock.restart();
    this->_t = 0;
}

EventsSfml::~EventsSfml()
{

}

void    EventsSfml::handleInputs()
{
    if (_t >= TICKRATE)
    {
        this->getKeyboardInput();
        this->getJoystickInput();
        _t = 0;
    }
    else
        _t += this->clock.restart().asMilliseconds();
}

void    EventsSfml::getKeyboardInput(void)
{
    for (auto button = _buttonPressed.begin(); button != this->_buttonPressed.end(); ++button)
    {
        if (sf::Keyboard::isKeyPressed(button->first))
        {
            ButtonEvent event(EVENT_BUTTON);
            event.setButtonType(button->second);
            Core::getInstance().useButtonEvent(event);
        }
    }
}

void    EventsSfml::getJoystickInput(void)
{
    if (sf::Joystick::isConnected(0))
    {
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        if (x > 20 || y > 20 || x < -20 || y < -20)
        {
            JoystickEvent   event;
            event.x = x;
            event.y = y;
            Core::getInstance().useJoystickEvent(event);
        }

        for (auto button = _joystickButtonPressed.begin(); button != this->_joystickButtonPressed.end(); ++button)
        {
            if (sf::Joystick::isButtonPressed(0, button->first))
            {
                ButtonEvent event(EVENT_BUTTON);
                event.setButtonType(button->second);
                Core::getInstance().useButtonEvent(event);
            }
        }
    }
}