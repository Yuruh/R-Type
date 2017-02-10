//
// Created by yuruh on 13/12/16.
//

#include <iostream>
#include "display/SoundManager.hpp"

SoundManager  SoundManager::_instance = SoundManager();

SoundManager::SoundManager()
{
    this->addSound("assets/sounds/big_laser.wav", SoundManager::LASER);
    this->addSound("assets/sounds/short_explosion_1.wav", SoundManager::EXPLOSION);
    this->addMusic("assets/sounds/stage_01.ogg", SoundManager::STAGE_1);
    this->addMusic("assets/sounds/menu.ogg", SoundManager::MENU);
}

SoundManager::~SoundManager()
{

}

SoundManager &SoundManager::Instance()
{
    return _instance;
}

void SoundManager::addSound(std::string const &path, SoundManager::SoundType type)
{
    if (!this->sounds[type].loadFromFile(path))
        this->sounds.erase(type);
}

void SoundManager::addMusic(std::string const &path, SoundManager::MusicType type)
{
    if (this->musics.find(type) == this->musics.end())
    {
        this->musics[type] = new sf::Music();
        this->musics[type]->openFromFile(path);
        this->musics[type]->setLoop(true);
    }
}

const sf::SoundBuffer &SoundManager::getSoundBuffer(SoundManager::SoundType type)
{
    if (this->sounds.find(type) != this->sounds.end())
        return (this->sounds[type]);
    else
        throw std::runtime_error("Could find sound element");
}

void SoundManager::playMusic(SoundManager::MusicType type)
{
    if (type != this->currentMusic && this->musics.find(type) != this->musics.end())
    {
        this->stopMusic(currentMusic);
        this->currentMusic = type;
        this->musics[type]->play();
    }
}

void SoundManager::stopMusic(SoundManager::MusicType type)
{
    if (this->musics.find(type) != this->musics.end())
        this->musics[type]->stop();
}

void SoundManager::setVolumeMusic(float volume)
{
    for (auto it = this->musics.begin(); it != this->musics.end(); ++it)
        it->second->setVolume(volume);
}

float SoundManager::getVolume()
{
    if (this->musics.find(currentMusic) != this->musics.end())
        return this->musics[currentMusic]->getVolume();
    return 20;
}
