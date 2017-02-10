//
// Created by yuruh on 30/11/16.
//

#include "display/WindowSfml.hpp"

WindowSfml::~WindowSfml()
{

}

void    WindowSfml::handleEvents(bool *tmp)
{
    sf::Event   event;
    while (this->pollEvent(event))
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            *tmp = true;
}

WindowSfml::WindowSfml(sf::VideoMode mode, std::string const& title) : sf::RenderWindow(mode, title, sf::Style::Close)
{
	this->setActive(false);
}

void WindowSfml::quit()
{
    this->close();
}
