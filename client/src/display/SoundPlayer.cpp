//
// Created by yuruh on 13/12/16.
//

#include <SFML/Audio/Sound.hpp>
#include "display/SoundPlayer.hpp"
#include "display/SoundManager.hpp"

SoundPlayer::SoundPlayer()
{
    this->sound = NULL;
}

SoundPlayer::SoundPlayer(SoundManager::SoundType type)
{
    if (this->sound)
        this->sound->setBuffer(SoundManager::Instance().getSoundBuffer(type));
}

void SoundPlayer::playSound()
{
    if (this->sound)
    {
        this->sound->setVolume(SoundManager::Instance().getVolume() / 3);
        this->sound->play();
    }
}

SoundPlayer::~SoundPlayer()
{
    if (this->sound != NULL)
        delete  this->sound;
}
