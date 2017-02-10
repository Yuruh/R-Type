//
// Created by babou on 17/12/16.
//

#include <display/TileSetSprites.hpp>
#include <display/ObjectPool.hpp>
#include <display/TextureManager.hpp>
#include <iostream>
#include <Core.hpp>
#include "display/menu/ChooseGameScreen.hpp"

ChooseGameScreen::ChooseGameScreen(WindowSfml *window) :
        AScene(SoundManager::MENU),
        background(TextureManager::get(TextureManager::BACKGROUND_MENU)),
        box(TextureManager::get(TextureManager::BOX_CHOOSE_GAME))
{
    this->window = window;
    this->choose_game = false;
    this->reset_grid = false;

    buttons.push_back(new Selectable(TextureManager::get(TextureManager::QUIT_NM), TextureManager::get(TextureManager::QUIT_HV)));
    buttons.push_back(new Selectable(TextureManager::get(TextureManager::SETTINGS_NM), TextureManager::get(TextureManager::SETTINGS_HV)));
    buttons.push_back(new Selectable(TextureManager::get(TextureManager::JOIN_NM), TextureManager::get(TextureManager::JOIN_HV)));
    buttons.push_back(new Selectable(TextureManager::get(TextureManager::CREATE_NM), TextureManager::get(TextureManager::CREATE_HV)));

    const float posButton[4] = {0.255f,      // Button quit
                                0.372f,      // Button Settings
                                0.518f,      // Button Join
                                0.635f };    // Button Create

    for (size_t i = 0; i < buttons.size(); i += 1)
        buttons[i]->move(WIN_X * posButton[i], WIN_Y * 0.817f);
    buttons[0]->setSelected(true);

    count = 0;
    game = 0;
    beginGame = 0;
}

ChooseGameScreen::~ChooseGameScreen()
{
}

void  ChooseGameScreen::update(float deltaTime)
{
    if (reset_grid)
    {
        for (unsigned int i = 0; i < this->gridBarre.size(); ++i)
            delete this->gridBarre[i];
        gridBarre.clear();
        size_t pos = 0;
        for (unsigned int i = 0; i < this->buttonValue.size(); ++i)
        {
            if (pos == 25)
                pos = 0;
            Button  *elem = new Button(TextureManager::get(TextureManager::GRID_BARRE), TextureManager::get(TextureManager::GRID_BARRE_SELECTED));
            elem->setPosition(WIN_X * 0.254f, ((pos++ * 26) + (WIN_Y * 0.190f)));
            elem->setText(std::to_string(this->buttonValue[i]), 20);
            gridBarre.push_back(elem);
        }
        this->reset_grid = false;
    }
    for (size_t i = 0; i < buttons.size(); i++)
        buttons[i]->addTime(deltaTime);
    for (size_t i = 0; i < gridBarre.size(); i++)
        gridBarre[i]->addTime(deltaTime);
}

void  ChooseGameScreen::useButtonEvent(const ButtonEvent &buttonEvent)
{
    if (!choose_game)
    {
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
    else if (choose_game && !this->gridBarre.empty())
    {
        beginGame = 0;
        for (size_t searchBegin = 1; searchBegin < game; searchBegin++)
            if (searchBegin % 25 == 0)
                beginGame += 1;

        if (buttonEvent.getButtonType() == UP && gridBarre[game]->isReady() && game > 0)
        {
            gridBarre[game--]->setSelected(false);
            gridBarre[game]->setSelected(true);
        }
        if (buttonEvent.getButtonType() == DOWN && gridBarre[game]->isReady() && game < gridBarre.size() - 1)
        {
            gridBarre[game++]->setSelected(false);
            gridBarre[game]->setSelected(true);
        }

        if (buttonEvent.getButtonType() == LEFT && gridBarre[game]->isReady() && game > 0)
        {
            gridBarre[game]->setSelected(false);
            game = (game - 10 < 0) ? 0 : game - 10;
            gridBarre[game]->setSelected(true);
        }

        if (buttonEvent.getButtonType() == RIGHT && gridBarre[game]->isReady() && game < gridBarre.size() - 1)
        {
            gridBarre[game]->setSelected(false);
            game = (game + 10 > gridBarre.size() - 1) ? gridBarre.size() - 1 : game + 10;
            gridBarre[game]->setSelected(true);
        }

        if (buttonEvent.getButtonType() == RETURN && gridBarre[game]->isReady())
        {
            if (game < buttonValue.size())
            {
                gridBarre[game]->setSelected(true);
                Core::getInstance().sendJoinGame(buttonValue[game]);
            }
        }
    }

    if (count == 0)
    {
        // QUIT GAME
        if (buttonEvent.getButtonType() == RETURN && buttons[count]->isReady())
                this->window->quit();
    }
    if (count == 1 && buttonEvent.getButtonType() == RETURN && buttons[count]->isReady())
    {
        buttons[count]->setSelected(true);
        // GO TO SETTINGS SCREEN
        setActive(false);
        if (links.find(SETTINGS) != links.end())
            links[SETTINGS]->setActive(true);
    }
    if (count == 2 && buttons[count]->isReady() && !gridBarre.empty())
    {
        // JOIN GAME
        if (!choose_game && buttonEvent.getButtonType() == RETURN)
        {
            choose_game = true;
            game = 0;
            gridBarre[game]->setSelected(true);
            buttons[count]->setSelected(false);
        }
        if (choose_game && buttonEvent.getButtonType() == BACKSPACE)
        {
            choose_game = false;
            gridBarre[game]->setSelected(false);
            buttons[count]->setSelected(true);
        }
    }
    if (count == 3 && buttonEvent.getButtonType() == RETURN && buttons[count]->isReady())
    {
        buttons[count]->setSelected(true);
        // GO TO ROOM SCREEN

        Core::getInstance().sendCreateGame();
    }
}

void    ChooseGameScreen::useGameInfo(GameInfo const& gameInfo)
{
    if (gameInfo.getType() == GAME_JOINED || gameInfo.getType() == GAME_LAUNCHED)
    {
        setActive(false);
        if (links.find(ROOM) != links.end())
        {
            links[ROOM]->setActive(true);
            links[ROOM]->useGameInfo(gameInfo);
        }
    }
}

void  ChooseGameScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(box);
    for (size_t pos = 0; pos < this->buttons.size(); pos++)
        target.draw(*buttons[pos]);

    for (size_t pos = 0 + (25 * beginGame); pos < 25 + (25 * beginGame); pos++)
    {
        if (pos == this->gridBarre.size())
            break;
        target.draw(*gridBarre[pos]);
    }
}

void ChooseGameScreen::setActive(bool value)
{
    AScene::setActive(value);
    if (value)
        Core::getInstance().requireGameList();
}

void ChooseGameScreen::useGameList(const GameList &list)
{
    if (list.getType() == GAME_LIST)
    {
        if (this->choose_game)
        {
            buttons[2]->setSelected(true);

            count = 2;
            game = 0;
            beginGame = 0;
            choose_game = false;
        }
        this->buttonValue.clear();
        for (unsigned int j = 0; j < list.gameIDs.size(); ++j)
            this->buttonValue.push_back(list.gameIDs[j]);
        this->reset_grid = true;
    }
}
