//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_TEXTUREMANAGER_HPP
#define RTYPE_TEXTUREMANAGER_HPP


#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager
{
public:
    enum TextureType {
        STARFIELD, SPACEBUBBLE, VORTEX, BRAINFART, EXPLOSION, TILE2, TILE3,
        BACKGROUND_TITLE_SCREEN, LOGO, PLAYER, ENNEMI_SHIP, TAZ,
        BACKGROUND_MENU, BOX_CHOOSE_GAME, BOX_SETTINGS, BOX_ROOM,
        BACKGROUND_GAUGE, FILLED_GAUGE, GRID_BARRE_SELECTED, GRID_BARRE,
        CHECKED_BOX, UNCHECKED_BOX,
        TEXT_BOX, TEXT_BOX_HV,
        BACK_NM, BACK_HV,
        CREATE_NM, CREATE_HV,
        GO_NM, GO_HV,
        JOIN_NM, JOIN_HV,
        OK_NM, OK_HV,
        QUIT_NM, QUIT_HV,
        SETTINGS_NM, SETTINGS_HV
    };

    static TextureManager &Instance();
    void    addTexture(std::string const&, TextureType);
    const sf::Texture &getTexture(TextureType);
    static const sf::Texture &get(TextureType);
private:
    static TextureManager _instance;

    TextureManager ();
    virtual ~TextureManager ();
    std::map<TextureType, sf::Texture> textures;
};


#endif //RTYPE_TEXTUREMANAGER_HPP
