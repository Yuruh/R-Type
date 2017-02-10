//
// Created by yuruh on 30/11/16.
//

#include "display/Selectable.hpp"

Selectable::Selectable(sf::Texture const& text1, sf::Texture const& text2)
{
    this->sprites.push_back(SfmlSpriteHandler(text1));
    this->sprites.push_back(SfmlSpriteHandler(text2));
//    this->active.setTexture(text2);
    this->selected = false;
    t = 0;
}

Selectable::~Selectable()
{

}

void      Selectable::setSelected(bool isSelected)
{
    t = 0;
    this->selected = isSelected;
}

void      Selectable::addTime(float deltaTime)
{
  this->t += deltaTime;
}

bool      Selectable::isReady() const
{
  return (this->t > SELETECTED_MIN_TIME);
}

void      Selectable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;

    if (this->sprites.empty())
    {
      std::cerr << "[DISPLAY ERROR] Sprites unset" << std::endl;
      return;
    }

    if (this->selected && this->sprites.size() >= 2)
    {
        target.draw(this->sprites[1]);
    }
    else
    {
        target.draw(this->sprites[0]);
    }
}

