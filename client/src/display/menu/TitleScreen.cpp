//
// Created by babou on 17/12/16.
//

#include <display/TileSetSprites.hpp>
#include <display/ObjectPool.hpp>
#include <display/TextureManager.hpp>
#include "display/menu/TitleScreen.hpp"

TitleScreen::TitleScreen() : AScene(SoundManager::MENU),
               background(TextureManager::get(TextureManager::BACKGROUND_TITLE_SCREEN)),
               logo(TextureManager::get(TextureManager::LOGO))
{
}

TitleScreen::~TitleScreen()
{

}

void  TitleScreen::update(float deltaTime)
{
}

void  TitleScreen::useButtonEvent(const ButtonEvent &buttonEvent)
{
    if (buttonEvent.getButtonType() == RETURN ||
            buttonEvent.getButtonType() == SPACE)
    {
        this->setActive(false);
        if (this->links.find(CHOOSE_GAME) != this->links.end())
            this->links[CHOOSE_GAME]->setActive(true);
    }
}

void  TitleScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(logo);
}
