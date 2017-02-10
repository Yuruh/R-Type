//
// Created by yuruh on 08/12/16.
//

#ifndef RTYPE_AMOVING_HPP
#define RTYPE_AMOVING_HPP


#include <EntityType.hpp>
#include <SFML/Audio/Sound.hpp>
#include "IAnimatedSprites.hpp"
#include "SoundPlayer.hpp"

class AEntity : public IAnimatedSprites, public SoundPlayer
{
protected:
    int     speed;
    float   x_dir;
    float   y_dir;
    EntityType  type;
    float           blinkTime;
    bool            blinking;

public:
    virtual void    update(float);

    AEntity(int speed, EntityType);
    AEntity();
    virtual ~AEntity();

    void    blink();
    void setSpeed(int speed);
    void setDirection(float x, float y);
    EntityType getName() const;
    virtual bool    isDone(int winWidth, int winHeight);

    virtual void reset() = 0;
};


#endif //RTYPE_AMOVING_HPP
