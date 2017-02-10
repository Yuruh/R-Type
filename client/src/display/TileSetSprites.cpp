//
// Created by yuruh on 01/12/16.
//

#include <iostream>
#include <display/TextureManager.hpp>
#include "display/TileSetSprites.hpp"

TileSetSprites::TileSetSprites(sf::Texture const& tileset, sf::IntRect rect, int qty, float refreshRate, bool repeated) : AEntity(100, UNDEFINED_ENTITY)
{
    this->reset();
    this->refreshRate = refreshRate;
    this->repeat = repeated;
    this->addSprites(tileset, rect, qty);
}

TileSetSprites::TileSetSprites(EntityType entityName)
{
    this->reset();
    this->repeat = true;

    if (entityName == BRAINFART)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::BRAINFART));
        this->addSprites(text, sf::IntRect(0, 0, text.getSize().x, text.getSize().y), 8);
        this->refreshRate = 0.03f;
        this->type = BRAINFART;
        this->setProportionalSize(BRAINFART_SIZE * 1080.0f / 100.0f, BRAINFART_SIZE * 1080.0f / 100.0f);
    }

    if (entityName == ENEMY_SHIP)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::ENNEMI_SHIP));
        this->addSprites(text, sf::IntRect(0, 0, text.getSize().x / 2, text.getSize().y), 8);
        this->refreshRate = 0.1f;
        this->type = ENEMY_SHIP;
        this->setProportionalSize(ENNEMY_SIZE * 1080.0f / 100.0f, ENNEMY_SIZE * 1080.0f / 100.0f);
    }

    if (entityName == TAZ)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::TAZ));
        this->addSprites(text, sf::IntRect(0, 0, text.getSize().x, text.getSize().y / 2), 8);
        this->addSprites(text, sf::IntRect(0, text.getSize().y / 2, text.getSize().x, text.getSize().y / 2), 8);
        this->refreshRate = 0.03f;
        this->type = TAZ;
        this->setProportionalSize(TAZ_SIZE * 1080.0f / 100.0f, TAZ_SIZE * 1080.0f / 100.0f);
    }

    if (entityName == SILENT_DEATH)
    {
        this->refreshRate = 0.0f;
        this->repeat = false;
        this->type = SILENT_DEATH;
    }

    if (entityName == EXPLOSION)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::EXPLOSION));
        this->addSprites(text, sf::IntRect(127, 0, text.getSize().x / 2 - 127, 32), 6);
        this->refreshRate = 0.06f;
        this->type = EXPLOSION;
        this->repeat = false;
        this->sound = new sf::Sound(SoundManager::Instance().getSoundBuffer(SoundManager::EXPLOSION));
        this->setProportionalSize(PLAYER_SIZE * 2 * 1080.0f / 100.0f, PLAYER_SIZE * 2 * 1080.0f / 100.0f);
    }

    if (entityName == MISSILE)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::TILE2));
        this->addSprites(text, sf::IntRect(87, 311, 70, 7), 2);
        this->refreshRate = 0.1f;
        this->type = MISSILE;
        this->sound = new sf::Sound(SoundManager::Instance().getSoundBuffer(SoundManager::LASER));
        this->setProportionalSize(MISSILE_SIZE * 1080.0f / 100.0f, MISSILE_SIZE * 1080.0f / 100.0f);
    }

    if (entityName == MISSILE_WAVE)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::TILE2));
        this->addSprites(text, sf::IntRect(228, 450, 75, 20), 4);
        this->refreshRate = 0.05f;
        this->type = MISSILE_WAVE;
        this->sound = new sf::Sound(SoundManager::Instance().getSoundBuffer(SoundManager::LASER));
        this->setProportionalSize(MISSILE_WAVE_SIZE * 1080.0f / 100.0f, MISSILE_WAVE_SIZE * 1080.0f / 100.0f);
    }

    if (entityName == SIDE_MISSILE_2)
    {
        sf::Texture const& text = TextureManager::get((TextureManager::TILE2));
        this->addSprites(text, sf::IntRect(87, 328, 70, 7), 2);
        this->refreshRate = 0.1f;
        this->type = SIDE_MISSILE_2;
    }
}

TileSetSprites::~TileSetSprites()
{}

void TileSetSprites::reset()
{
    this->t = 0;
    this->counter = 0;
    this->blinkTime = 0;
    this->blinking = false;
}

void TileSetSprites::update(float deltaTime)
{
    AEntity::update(deltaTime);
    t += deltaTime;
    if (t > this->refreshRate)
    {
        if (this->repeat || counter < this->sprites.size())
        {
            t = 0;
            counter++;
        }
        if (this->repeat && counter == this->sprites.size())
            counter = 0;
    }
}

void TileSetSprites::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    if (this->counter < this->sprites.size() && this->counter >= 0)
        target.draw(this->sprites[this->counter]);
}

void TileSetSprites::addSprites(const sf::Texture &tileset, sf::IntRect rect, int qty)
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

bool TileSetSprites::isDone(int winWidth, int winHeight)
{
    if (!this->repeat && this->counter == this->sprites.size() && t > this->refreshRate)
        return true;
    else
        return AEntity::isDone(winWidth, winHeight);
}
