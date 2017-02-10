//
// Created by yuruh on 01/12/16.
//

#ifndef RTYPE_ISCENE_HPP
#define RTYPE_ISCENE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <Serializable/GameList.hpp>
#include <Serializable/GameInfo.hpp>
#include "IAnimated.hpp"
#include "ButtonEvent.hpp"

enum SceneType
{
    CHOOSE_GAME,
    ROOM,
    SETTINGS,
    TITLE,
    GAME
};
class   IScene : public IAnimated
{
public:
    virtual void useButtonEvent(const ButtonEvent &buttonEvent) = 0;
    virtual bool isActive() const = 0;
    virtual void setActive(bool)= 0;
    virtual void useEntityPos(const EntityPos &entityPos)=0;
    virtual void useGameList(const GameList &list)=0;
    virtual void useGameInfo(const GameInfo &list)=0;
    virtual void useGameResult(const SimpleInfo &)=0;
    virtual void addLink(SceneType, IScene *)= 0;
};

#endif //RTYPE_ISCENE_HPP
