//
// Created by yuruh on 29/11/16.
//

#ifndef RTYPE_DISPLAYSFML_HPP
#define RTYPE_DISPLAYSFML_HPP

#include "IDisplay.hpp"
#include "WindowSfml.hpp"
#include "menu/TitleScreen.hpp"
#include "menu/ChooseGameScreen.hpp"
#include "menu/RoomScreen.hpp"
#include "menu/SettingsScreen.hpp"
#include "TileSetSprites.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <EntityPos.hpp>
#include <ButtonEvent.hpp>
#include <ThreadPool.hpp>

class DisplaySfml : public IDisplay
{
private:
    ThreadPool    pool;
    WindowSfml    *window;
    sf::Clock       clock;
    std::vector<IScene *>   scenes;
    bool            hasFocus;
public:
    DisplaySfml();
    ~DisplaySfml();

    IWindow *init();
    void update();
    void loadStuff();
    bool isActive();

    void modifyEntityPos(const EntityPos &entityPos);
    void useButtonEvent(const ButtonEvent &buttonEvent);

    void useGameList(const GameList &list);

    void useGameInfo(const GameInfo &info);
    void useGameResult(const SimpleInfo &);
};


#endif //RTYPE_DISPLAYSFML_HPP
