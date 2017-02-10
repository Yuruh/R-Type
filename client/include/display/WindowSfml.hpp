//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_WINDOWSFML_HPP
#define RTYPE_WINDOWSFML_HPP


#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IWindow.hpp"

class WindowSfml : public IWindow, public sf::RenderWindow
{
public:
    WindowSfml(sf::VideoMode, std::string const&);
    ~WindowSfml();

    void handleEvents(bool *);

    void quit();
};


#endif //RTYPE_WINDOWSFML_HPP
