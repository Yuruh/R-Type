//
// Created by babou on 17/12/16.
//

#ifndef RTYPE_CONNECTIONSCREEN_HPP
#define RTYPE_CONNECTIONSCREEN_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "display/WindowSfml.hpp"
#include "display/Selectable.hpp"
#include "display/Button.hpp"
#include "display/AScene.hpp"
#include "display/TileSetSprites.hpp"

class ChooseGameScreen : public AScene
{
private:
    std::vector<Selectable*> buttons;
    std::vector<Button*> gridBarre;

//  To use sf::Font in the main  thread;
    std::vector<uint32_t>    buttonValue;

    SfmlSpriteHandler   background;
    SfmlSpriteHandler   box;
    bool                choose_game;
    bool                reset_grid;
    size_t              count;
    unsigned int        game;
    size_t              beginGame;

    WindowSfml          *window;

    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    ChooseGameScreen (WindowSfml*);
    virtual ~ChooseGameScreen ();
    virtual void useButtonEvent(const ButtonEvent &buttonEvent);
    virtual void useGameList(const GameList &list);
    virtual void update(float);

    void setActive(bool value);

    void useGameInfo(const GameInfo &gameInfo);
};

#endif //RTYPE_CONNECTIONSCREEN_HPP
