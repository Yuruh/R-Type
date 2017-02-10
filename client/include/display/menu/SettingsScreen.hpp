//
// Created by babou on 17/12/16.
//

#ifndef RTYPE_SETTINGSSCREEN_HPP
#define RTYPE_SETTINGSSCREEN_HPP

#include    <SFML/Graphics/Drawable.hpp>
#include    "display/Button.hpp"
#include    "display/AScene.hpp"
#include    "display/TileSetSprites.hpp"
#include    "display/WindowSfml.hpp"
#include    <display/TileSetSprites.hpp>
#include    <display/ObjectPool.hpp>
#include    <display/TextureManager.hpp>
#include    <iostream>
class SettingsScreen : public AScene
{
private:
    WindowSfml              *window;

    std::vector<Button*>    buttons[2];
    SfmlSpriteHandler       background;
    SfmlSpriteHandler       box;
    SfmlSpriteHandler       background_gauge;

    sf::Text                resolution;
    int                     pos_res;
    const int               size_res[5][2] = { {800, 600}, {1280, 720},
                                               {1600, 900}, {1855, 1056},
                                               {1920, 1080} };

    std::vector<sf::Text>   keyboard;
    sf::Font                font;

    size_t                  count;

    float                   music_gauge;
    float                   old_music;
    sf::Text                music_text;

    virtual void            draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    SettingsScreen (WindowSfml*);
    virtual ~SettingsScreen ();
    virtual void            useButtonEvent(const ButtonEvent &buttonEvent);
    virtual void            update(float);
};

#endif //RTYPE_SETTINGSSCREEN_HPP
