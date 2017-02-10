//
// Created by yuruh on 30/12/16.
//

#ifndef SHARED_JOYSTICKEVENT_HPP
#define SHARED_JOYSTICKEVENT_HPP

# include "ASerializable.hpp"

struct 			JoystickEvent : public ASerializable
{
public:
    JoystickEvent();
    ~JoystickEvent();

    std::string           serialize() const;
    void            operator<<(const char*);
    ISerializable* 		clone() const;


    float           x;
    float           y;
};

std::ostream&       operator<<(std::ostream &os, const JoystickEvent&);

#endif //SHARED_JOYSTICKEVENT_HPP
