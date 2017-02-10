//
// Created by yuruh on 29/11/16.
//

#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <Serializable/GameList.hpp>
#include "display/DisplaySfml.hpp"
#include "display/GameScene.hpp"

DisplaySfml::DisplaySfml()
{
    this->window = NULL;
    this->hasFocus = true;
}

IWindow* DisplaySfml::init()
{
    this->window = new WindowSfml(sf::VideoMode(WIN_X, WIN_Y), "R-TYPE");
    this->clock.restart();

    IScene    *title = new TitleScreen();
    IScene    *menu = new ChooseGameScreen(window);
    IScene    *room = new RoomScreen();
    IScene    *settings = new SettingsScreen(window);
    IScene    *game = new GameScene(SoundManager::STAGE_1);
	title->addLink(CHOOSE_GAME, menu);
    menu->addLink(SETTINGS, settings);
    menu->addLink(ROOM, room);
    settings->addLink(CHOOSE_GAME, menu);
    room->addLink(CHOOSE_GAME, menu);
    room->addLink(GAME, game);
    game->addLink(CHOOSE_GAME, menu);

    title->setActive(true);

    this->scenes.push_back(title);
    this->scenes.push_back(menu);
    this->scenes.push_back(settings);
    this->scenes.push_back(room);
    this->scenes.push_back(game);

    pool.start(1);

    return this->window;
}

void DisplaySfml::useGameList(const GameList &list)
{
    for (unsigned int i = 0; i < this->scenes.size(); ++i)
        if (this->scenes[i]->isActive())
            this->scenes[i]->useGameList(list);
}

void DisplaySfml::useGameInfo(const GameInfo &info)
{
    for (unsigned int i = 0; i < this->scenes.size(); ++i)
        if (this->scenes[i]->isActive())
            this->scenes[i]->useGameInfo(info);
}

void DisplaySfml::loadStuff()
{
}

bool DisplaySfml::isActive()
{
    return this->window->isOpen();
}

void DisplaySfml::update()
{
    sf::Event   event;
    float deltaTime = this->clock.restart().asSeconds();
    this->window->clear();

    for (unsigned int i = 0; i < this->scenes.size(); ++i)
    {
        if (this->scenes[i]->isActive())
        {
			this->scenes[i]->update(deltaTime);
            this->window->draw(*this->scenes[i]);
        }
    }
    while (this->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::GainedFocus)
            this->hasFocus = true;
        if (event.type == sf::Event::LostFocus)
            this->hasFocus = false;
    }
	//this->window->setActive(false);
	this->window->display();
	//this->window->setActive(true);
}

DisplaySfml::~DisplaySfml()
{
    pool.stop();
    for (unsigned int i = 0; i < this->scenes.size(); ++i)
        delete this->scenes[i];
}

void DisplaySfml::modifyEntityPos(const EntityPos &entityPos)
{
    for (unsigned int i = 0; i < this->scenes.size(); ++i)
        if (this->scenes[i]->isActive())
            pool.enqueue(&IScene::useEntityPos, this->scenes[i], entityPos);
}

void DisplaySfml::useButtonEvent(const ButtonEvent &buttonEvent)
{
	if (!hasFocus)
		return;
	for (unsigned int i = 0; i < this->scenes.size(); ++i)
		if (this->scenes[i]->isActive())
		{
			this->scenes[i]->useButtonEvent(buttonEvent);
		}
}
void DisplaySfml::useGameResult(const SimpleInfo &info)
{
    for (unsigned int i = 0; i < this->scenes.size(); ++i)
        if (this->scenes[i]->isActive())
            this->scenes[i]->useGameResult(info);
}
