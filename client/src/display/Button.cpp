//
// Created by yuruh on 30/11/16.
//

#include <iostream>
#include "display/Button.hpp"


Button::Button(sf::Texture const& text1, sf::Texture const& text2) : Selectable(text1, text2)
{
    this->font.loadFromFile("assets/rtype_font.ttf");
    this->title.setFont(this->font);
    this->title.setColor(sf::Color(138, 212, 241, 255));
}

Button::~Button()
{

}

void   Button::setText(std::string const& title, unsigned int size)
{
    this->title.setString(title);
    this->title.setCharacterSize(size);

    sf::FloatRect textRect = this->title.getLocalBounds();
    this->title.setPosition(this->getPosition());
    this->title.move(this->getWidth() / 2.0f - textRect.width / 2.0f,
                     this->getHeight() / 2.0f - textRect.height * 1.6f);
}

void   Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Selectable::draw(target, states);
    target.draw(this->title);
}
