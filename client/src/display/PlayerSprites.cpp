//
// Created by yuruh on 29/12/16.
//

#include <display/TextureManager.hpp>
#include "display/PlayerSprites.hpp"

PlayerSprites::PlayerSprites(EntityType entityName)
{
    this->reset();
    if (entityName == PLAYER1)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::PLAYER));
        this->addSprites(text, sf::IntRect(0, 0, text.getSize().x, text.getSize().y / 5), 5);
        this->refreshRate = 0.1f;
        this->type = PLAYER1;
        this->setProportionalSize(PLAYER_SIZE * 1080 / 100, PLAYER_SIZE * 1080 / 100);
    }

    if (entityName == PLAYER2)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::PLAYER));
        this->addSprites(text, sf::IntRect(0, text.getSize().y / 5, text.getSize().x, text.getSize().y / 5), 5);
        this->refreshRate = 0.1f;
        this->type = PLAYER2;
        this->setProportionalSize(PLAYER_SIZE * 1080 / 100, PLAYER_SIZE * 1080 / 100);
    }

    if (entityName == PLAYER3)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::PLAYER));
        this->addSprites(text, sf::IntRect(0, text.getSize().y / 5 * 2, text.getSize().x, text.getSize().y / 5), 5);
        this->refreshRate = 0.1f;
        this->type = PLAYER3;
        this->setProportionalSize(PLAYER_SIZE * 1080 / 100, PLAYER_SIZE * 1080 / 100);
    }

    if (entityName == PLAYER4)
    {
        sf::Texture const &text = TextureManager::get((TextureManager::PLAYER));
        this->addSprites(text, sf::IntRect(0, text.getSize().y / 5 * 3, text.getSize().x, text.getSize().y / 5), 5);
        this->refreshRate = 0.1f;
        this->type = PLAYER4;
        this->setProportionalSize(PLAYER_SIZE * 1080 / 100, PLAYER_SIZE * 1080 / 100);
    }
}

PlayerSprites::~PlayerSprites()
{

}

void PlayerSprites::update(float deltaTime)
{
    t += deltaTime;
    if (t > this->refreshRate)
    {
        if (this->y_dir < 0)
        {
            if (counter < 4)
                counter++;
        }
        else if (this->y_dir > 0)
        {
            if (counter > 0)
                counter--;
        }
        else
        {
            if (counter < 2)
                counter++;
            else if (counter > 2)
                counter--;
        }
        t = 0;
    }
}

//TODO : ça in AEntity
void PlayerSprites::addSprites(const sf::Texture &tileset, sf::IntRect rect, int qty)
{
    int offset = rect.left;
    size_t size = this->sprites.size();

    for (int i = 0; i < qty; ++i)
    {
        this->sprites.push_back(SfmlSpriteHandler(tileset));
        this->sprites[i + size].setTextureRect(offset, rect.top, rect.width / qty, rect.height);
        offset += rect.width / qty;
    }
}

void PlayerSprites::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    if (this->counter < this->sprites.size() && this->counter >= 0)
        target.draw(this->sprites[this->counter]);
}

void PlayerSprites::reset()
{
    this->t = 0;
    this->counter = 2;
    this->blinkTime = 0;
    this->blinking = false;
}
