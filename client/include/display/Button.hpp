//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_BUTTON_HPP
#define RTYPE_BUTTON_HPP


#include "Selectable.hpp"

class Button : public Selectable
{
protected:
    sf::Font    font;
    sf::Text    title;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Button (sf::Texture const&, sf::Texture const&);
    void  setText(std::string const&, unsigned int);
    virtual ~Button ();
};

#endif //RTYPE_BUTTON_HPP
