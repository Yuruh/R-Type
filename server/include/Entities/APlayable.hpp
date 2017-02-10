//
// Created by wasta-geek on 22/12/16.
//

#ifndef SERVER_RTYPE_APLAYABLE_HPP
#define SERVER_RTYPE_APLAYABLE_HPP

#define SHOOT_COOLDOWN  333
#define WAVE_COOLDOWN  5000

#include <Serializable/ButtonEvent.hpp>
#include <map>
#include <vector>
#include <Serializable/JoystickEvent.hpp>
#include "AEntity.hpp"
#include "ANonPlayable.hpp"
#include "Missiles/AMissile.hpp"

class APlayable : public AEntity
{
public:
    APlayable();

    virtual ~APlayable();

    virtual void setPosition(float x, float y) override;

    virtual const std::pair<float, float> &getDirection() const;

    virtual void takeDmg(uint32_t hp);

    uint32_t getHp() const;

    void setHp(uint32_t hp);

    std::string const &getName() const;

    void setName(std::string const &name);

    unsigned int getNetworkID() const;

    void setNetworkID(uint32_t i);
    void setEvent(ButtonEvent const&);
    void setEvent(JoystickEvent const&);
    virtual void update(float deltaTime, std::vector<AMissile *> &) = 0;
protected:
    std::pair<float, float>   _dir;
    uint32_t _hp;
    std::string _name;
    unsigned int    _networkID;
    std::map<ButtonType, bool>  events;
    float joystickX;
    float joystickY;
    void resetEvents();
};


#endif //SERVER_RTYPE_APLAYABLE_HPP
