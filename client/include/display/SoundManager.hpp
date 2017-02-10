//
// Created by yuruh on 13/12/16.
//

#ifndef RTYPE_SOUNDMANAGER_HPP
#define RTYPE_SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
public:
    enum SoundType { UNDEFINED_SOUND, LASER, EXPLOSION };
    enum MusicType { UNDEFINED_MUSIC, MENU, STAGE_1};

    static SoundManager &Instance();

    void addSound(std::string const&, SoundType);
    void addMusic(const std::string &path, MusicType type);

    const sf::SoundBuffer &getSoundBuffer(SoundType);
    void playMusic(MusicType type);
    void stopMusic(MusicType type);
    void setVolumeMusic(float volume);

    float getVolume();
//    void playMusic(MusicType type);
//    sf::Music & getMusic(MusicType type);

private:
    static SoundManager _instance;

    SoundManager ();
    virtual ~SoundManager ();
    std::map<SoundType, sf::SoundBuffer> sounds;
    std::map<MusicType, sf::Music*>      musics;
    MusicType                           currentMusic;
};


#endif //RTYPE_SOUNDMANAGER_HPP
