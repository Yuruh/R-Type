//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_EVENTSSFML_HPP
#define RTYPE_EVENTSSFML_HPP

#include <map>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Joystick.hpp>
#include "IEventManager.hpp"
#include "display/IWindow.hpp"
#include "ButtonEvent.hpp"
#include "JoystickEvent.hpp"

class EventsSfml : public IEventManager
{
    std::map<sf::Keyboard::Key, ButtonType> _buttonPressed;
    std::map<uint32_t, ButtonType> _joystickButtonPressed;
    sf::Clock   clock;
    float _t;

public:
    EventsSfml();
    ~EventsSfml();

    virtual void    getKeyboardInput(void);
    virtual void    getJoystickInput(void);
    virtual void            handleInputs();
};


#endif //RTYPE_EVENTSSFML_HPP
