//
// Created by yuruh on 01/12/16.
//

#ifndef RTYPE_ASCENE_HPP
#define RTYPE_ASCENE_HPP


#include <SFML/Audio/Music.hpp>
#include <Serializable/EntityPos.hpp>
#include <Serializable/SimpleInfo.hpp>
#include "IScene.hpp"
#include "SoundManager.hpp"



class AScene : public IScene
{
private:
    bool        active;
protected:
    SoundManager::MusicType type;
    std::map<SceneType, IScene *> links;
public:
    AScene(SoundManager::MusicType type);
    virtual ~AScene();
    virtual void update(float)= 0;
    bool isActive() const;
    void setActive(bool);
//    virtual void useButtonEvent(const ButtonEvent &buttonEvent);
    virtual void useEntityPos(const EntityPos &entityPos);
    virtual void useGameList(const GameList &list);
    void addLink(SceneType, IScene *);
    virtual void useGameResult(const SimpleInfo& result);
    virtual void useGameInfo(const GameInfo &info);
};


#endif //RTYPE_ASCENE_HPP
