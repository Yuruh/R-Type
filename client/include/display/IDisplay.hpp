//
// Created by yuruh on 29/11/16.
//

#ifndef RTYPE_IDISPLAY_HPP
#define RTYPE_IDISPLAY_HPP


#include <Serializable/GameInfo.hpp>
#include <Serializable/SimpleInfo.hpp>
#include "IWindow.hpp"
#include "EntityPos.hpp"
#include "ButtonEvent.hpp"

# define    WIN_X   1920
# define    WIN_Y   1080

class IDisplay
{
public:
    virtual IWindow * init()= 0;
    virtual void update()= 0;
    virtual void loadStuff()= 0;
    virtual bool isActive()= 0;
    virtual void modifyEntityPos(const EntityPos &entityPos)= 0;
    virtual void useButtonEvent(const ButtonEvent &buttonEvent)= 0;
    virtual void useGameList(const GameList &list) =0;
    virtual void useGameInfo(const GameInfo &info)=0;
    virtual void useGameResult(const SimpleInfo &)= 0;
};


#endif //RTYPE_IDISPLAY_HPP
