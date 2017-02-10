//
// Created by yuruh on 13/12/16.
//

#ifndef RTYPE_SOUNDPLAYER_HPP
#define RTYPE_SOUNDPLAYER_HPP

#include <string>
#include <SFML/Audio/Sound.hpp>
#include "SoundManager.hpp"

class SoundPlayer
{
protected:
    sf::Sound       *sound;

public:
    SoundPlayer();
    SoundPlayer(SoundManager::SoundType type);
    ~SoundPlayer();

    void    playSound();
};


#endif //RTYPE_SOUNDPLAYER_HPP
