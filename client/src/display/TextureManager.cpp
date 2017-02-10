//
// Created by yuruh on 30/11/16.
//

#include <iostream>
#include "display/TextureManager.hpp"

TextureManager  TextureManager::_instance = TextureManager();

TextureManager::TextureManager()
{
    this->addTexture("assets/starfield_one.png", TextureManager::STARFIELD);
    this->addTexture("assets/r-typesheet3.png", TextureManager::SPACEBUBBLE);
    this->addTexture("assets/r-typesheet30a.png", TextureManager::VORTEX);
    this->addTexture("assets/r-typesheet17.png", TextureManager::BRAINFART);
    this->addTexture("assets/r-typesheet44.png", TextureManager::EXPLOSION);
    this->addTexture("assets/r-typesheet2.png", TextureManager::TILE2);
    this->addTexture("assets/r-typesheet16.png", TextureManager::TILE3);
    this->addTexture("assets/r-typesheet42.png", TextureManager::PLAYER);
    this->addTexture("assets/r-typesheet5.png", TextureManager::ENNEMI_SHIP);
    this->addTexture("assets/r-typesheet8.png", TextureManager::TAZ);

    this->addTexture("assets/menu/background_title_screen.png", TextureManager::BACKGROUND_TITLE_SCREEN);
    this->addTexture("assets/menu/logo_rtype2.png", TextureManager::LOGO);

    this->addTexture("assets/menu/background_menu.png", TextureManager::BACKGROUND_MENU);
    this->addTexture("assets/menu/box_choose_game.png", TextureManager::BOX_CHOOSE_GAME);
    this->addTexture("assets/menu/box_settings.png", TextureManager::BOX_SETTINGS);
    this->addTexture("assets/menu/box_room.png", TextureManager::BOX_ROOM);

    this->addTexture("assets/menu/GaugeBackground.png", TextureManager::BACKGROUND_GAUGE);
    this->addTexture("assets/menu/GaugeFilled.png", TextureManager::FILLED_GAUGE);
    this->addTexture("assets/menu/gridBarreSelected.png", TextureManager::GRID_BARRE_SELECTED);
    this->addTexture("assets/menu/gridBarre3.png", TextureManager::GRID_BARRE);
    this->addTexture("assets/menu/TextBox.png", TextureManager::TEXT_BOX);
    this->addTexture("assets/menu/TextBoxHover.png", TextureManager::TEXT_BOX_HV);

    this->addTexture("assets/menu/button/checkBoxUncheckedHover.png", TextureManager::UNCHECKED_BOX);
    this->addTexture("assets/menu/button/checkBoxCheckedHover.png", TextureManager::CHECKED_BOX);

    // Assets for normal button
    this->addTexture("assets/menu/button/buttonBackNormal.png", TextureManager::BACK_NM);
    this->addTexture("assets/menu/button/buttonCreateNormal.png", TextureManager::CREATE_NM);
    this->addTexture("assets/menu/button/buttonGoNormal.png", TextureManager::GO_NM);
    this->addTexture("assets/menu/button/buttonJoinNormal.png", TextureManager::JOIN_NM);
    this->addTexture("assets/menu/button/buttonOkNormal.png", TextureManager::OK_NM);
    this->addTexture("assets/menu/button/buttonQuitNormal.png", TextureManager::QUIT_NM);
    this->addTexture("assets/menu/button/buttonSettingsNormal.png", TextureManager::SETTINGS_NM);

    // Assets for hover (clicked is better) button
    this->addTexture("assets/menu/button/buttonBackClicked.png", TextureManager::BACK_HV);
    this->addTexture("assets/menu/button/buttonCreateClicked.png", TextureManager::CREATE_HV);
    this->addTexture("assets/menu/button/buttonGoHover.png", TextureManager::GO_HV);
    this->addTexture("assets/menu/button/buttonJoinClicked.png", TextureManager::JOIN_HV);
    this->addTexture("assets/menu/button/buttonOkClicked.png", TextureManager::OK_HV);
    this->addTexture("assets/menu/button/buttonQuitClicked.png", TextureManager::QUIT_HV);
    this->addTexture("assets/menu/button/buttonSettingsClicked.png", TextureManager::SETTINGS_HV);
}

TextureManager::~TextureManager()
{

}

TextureManager& TextureManager::Instance()
{
    return (_instance);
}

void    TextureManager::addTexture(std::string const& path, TextureType type)
{
    if (!this->textures[type].loadFromFile(path))
        this->textures.erase(type);
}

const sf::Texture &TextureManager::getTexture(TextureType type)
{
    if (this->textures.find(type) != this->textures.end())
        return (this->textures[type]);
    else
        throw std::runtime_error("Could not find texture");
}

const sf::Texture &TextureManager::get(TextureManager::TextureType type)
{
    return TextureManager::Instance().getTexture(type);
}
