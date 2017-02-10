//
// Created by babou on 18/12/16.
//

#include <display/TileSetSprites.hpp>
#include <display/ObjectPool.hpp>
#include <display/TextureManager.hpp>
#include <iostream>
#include <Core.hpp>
#include "display/menu/RoomScreen.hpp"

RoomScreen::RoomScreen() : AScene(SoundManager::MENU),
                           background(TextureManager::get(TextureManager::BACKGROUND_MENU)),
                           box(TextureManager::get(TextureManager::BOX_ROOM))
{
    buttons.push_back(new Selectable(TextureManager::get(TextureManager::BACK_NM), TextureManager::get(TextureManager::BACK_HV)));
    buttons.push_back(new Selectable(TextureManager::get(TextureManager::GO_NM), TextureManager::get(TextureManager::GO_HV)));

    shipPlayers.push_back(PlayerSprites(PLAYER1));
    shipPlayers.push_back(PlayerSprites(PLAYER2));
    shipPlayers.push_back(PlayerSprites(PLAYER3));
    shipPlayers.push_back(PlayerSprites(PLAYER4));

    const float posPlayer[4][4] = { {665, 200},
                                    {1170, 200},
                                    {665, 539},
                                    {1170, 539} };

    for (size_t i = 0; i < shipPlayers.size(); i += 1)
    {
        shipPlayers[i].move(posPlayer[i][0], posPlayer[i][1]);
    }

    const float posButton[2][2] = { {0.260f, 0.888f},     // Button Back
                                    {0.721f, 0.856f} };   // Button Go

    for (size_t i = 0; i < buttons.size(); i += 1)
        buttons[i]->move(WIN_X * posButton[i][0], WIN_Y * posButton[i][1]);
    buttons[0]->setSelected(true);

    gameId = 0;
    count = 0;
    reset_grid = false;

    font.loadFromFile("assets/rtype_font.ttf");

    this->roomId.setFont(font);
    this->roomId.setString("ROOM "+ std::to_string(this->gameId));
    this->roomId.setPosition(30, 30);
//    this->roomId.setColor(sf::Color(138, 212, 241, 255));
    this->roomId.setCharacterSize(50);
}

RoomScreen::~RoomScreen()
{
}

void  RoomScreen::update(float deltaTime)
{
    if (reset_grid)
    {
        for (size_t i = 0; i < idPlayers.size(); ++i)
            delete idPlayers[i];
        idPlayers.clear();

//        const float posIdPlayer[4][4] = { {540, 110} };
        const float posIdPlayer[4][4] = { {540, 110},
                                         {1045, 110},
                                         {540, 449},
                                         {1045, 449} };
        for (size_t i = 0; i < playerValue.size(); ++i)
        {
            sf::Text    *player = new sf::Text("ID: " + std::to_string(playerValue[i]),
                                               font);

            player->setPosition(posIdPlayer[i][0], posIdPlayer[i][1]);
//            player->setColor(sf::Color(138, 212, 241, 255));
            idPlayers.push_back(player);

        }
        this->reset_grid = false;
    }
    for (size_t i = 0; i < buttons.size(); i++)
        buttons[i]->addTime(deltaTime);
}

void  RoomScreen::useButtonEvent(const ButtonEvent &buttonEvent)
{
    if (buttonEvent.getButtonType() == RETURN)
    {
        if (buttons[count]->isReady())
        {
            if (count == 0)
            {
                buttons[count]->setSelected(true);
                this->setActive(false);
                if (this->links.find(CHOOSE_GAME) != this->links.end())
                    this->links[CHOOSE_GAME]->setActive(true);
                Core::getInstance().sendLeaveRoom(this->gameId);
            }
            if (count == 1)
                Core::getInstance().sendLaunchGame(this->gameId);
        }
    }

    if (buttonEvent.getButtonType() == LEFT && count > 0 && buttons[count]->isReady())
    {
        buttons[count--]->setSelected(false);
        buttons[count]->setSelected(true);
    }
    if (buttonEvent.getButtonType() == RIGHT && count < buttons.size() - 1 && buttons[count]->isReady())
    {
        buttons[count++]->setSelected(false);
        buttons[count]->setSelected(true);
    }
}

void  RoomScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(background);
    target.draw(box);
    target.draw(roomId);
    /*
    target.draw(shipPlayers[1]);
    target.draw(shipPlayers[2]);
    target.draw(shipPlayers[3]);
     */
    for (size_t pos = 0; pos < this->idPlayers.size(); pos++)
    {
        if (pos < shipPlayers.size())
            target.draw(shipPlayers[pos]);
        target.draw(*idPlayers[pos]);
    }
    for (size_t pos = 0; pos < this->buttons.size(); pos++)
        target.draw(*buttons[pos]);
}

void RoomScreen::useGameInfo(const GameInfo &info)
{
    if (info.getType() == GAME_JOINED)
    {
        this->gameId = info.getGameId();
        this->roomId.setString("ROOM "+ std::to_string(this->gameId));
    }
    else if (info.getType() == GAME_LAUNCHED)
    {
        if (info.getGameId() == this->gameId)
        {
            setActive(false);
            if (this->links.find(GAME) != this->links.end())
                this->links[GAME]->setActive(true);
        }
        else
            std::cerr << "LAUNCH GAME FAILED" << std::endl;
    }
}

void RoomScreen::useGameList(const GameList &ids)
{
    this->playerValue.clear();
    for (unsigned int j = 0; j < ids.gameIDs.size(); ++j)
        this->playerValue.push_back(ids.gameIDs[j]);
    this->reset_grid = true;
}

void RoomScreen::setActive(bool value)
{
    AScene::setActive(value);
    Core::getInstance().requireRoomInfo();
    buttons[0]->setSelected(true);

    count = 0;
}