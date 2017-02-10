//
// Created by babou on 17/12/16.
//

#ifndef RTYPE_TITLESCREEN_HPP
#define RTYPE_TITLESCREEN_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "display/AScene.hpp"
#include "display/TileSetSprites.hpp"

class TitleScreen : public AScene
{
private:
    SfmlSpriteHandler   background;
    SfmlSpriteHandler   logo;

    virtual void        draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    TitleScreen ();
    virtual ~TitleScreen ();
    virtual void useButtonEvent(const ButtonEvent &buttonEvent);
    virtual void update(float);
};

#endif //RTYPE_TITLESCREEN_HPP
