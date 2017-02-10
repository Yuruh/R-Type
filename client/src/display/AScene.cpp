//
// Created by yuruh on 01/12/16.
//

#include <display/SoundManager.hpp>
#include "display/AScene.hpp"

AScene::AScene(SoundManager::MusicType type) : type(type)
{
    this->active = false;
    SoundManager::Instance().setVolumeMusic(20.0);
}

AScene::~AScene()
{

}

bool AScene::isActive() const
{
    return this->active;
}


void AScene::setActive(bool value)
{
    this->active = value;
    if (this->active)
        SoundManager::Instance().playMusic(type);
//    else
//        SoundManager::Instance().stopMusic(type);
}

void AScene::addLink(SceneType type, IScene *scene)
{
    this->links[type] = scene;
}

//  Declared here to avoid useless definition
void AScene::useEntityPos(const EntityPos &entityPos)
{
    (void)entityPos;
}

void AScene::useGameList(const GameList &list)
{
    (void)list;
}

void AScene::useGameInfo(const GameInfo &info)
{
    (void)info;
}

void AScene::useGameResult(const SimpleInfo &result)
{
    (void)result;
}
