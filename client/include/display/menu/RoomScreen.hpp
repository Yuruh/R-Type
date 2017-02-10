//
// Created by babou on 18/12/16.
//

#ifndef RTYPE_ROOMSCREEN_HPP
#define RTYPE_ROOMSCREEN_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "display/Selectable.hpp"
#include "display/AScene.hpp"
#include "display/PlayerSprites.hpp"

class RoomScreen : public AScene
{
private:
    std::vector<uint32_t>   playerValue;
    bool                    reset_grid;

    std::vector<Selectable*>    buttons;
    std::vector<sf::Text*>      idPlayers;
    std::vector<PlayerSprites> shipPlayers;

    sf::Font            font;

    SfmlSpriteHandler   background;
    SfmlSpriteHandler   box;
    size_t              count;
    uint32_t            gameId;

    sf::Text            roomId;
    virtual void        draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    RoomScreen ();
    virtual ~RoomScreen ();
    virtual void useButtonEvent(const ButtonEvent &buttonEvent);
    virtual void update(float);
    void useGameInfo(const GameInfo &info);
    void setActive(bool value);
    void useGameList(const GameList &list);
};

#endif //RTYPE_ROOMSCREEN_HPP
