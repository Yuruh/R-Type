//
// Created by yuruh on 29/11/16.
//

#ifndef RTYPE_IEVENT_HPP
#define RTYPE_IEVENT_HPP

#define TICKRATE 17

class IEventManager
{
public:
    virtual void handleInputs() = 0;
    virtual void getKeyboardInput(void) = 0;
    virtual void getJoystickInput(void) = 0;
};

#endif //RTYPE_IEVENT_HPP
