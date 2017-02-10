//
// Created by yuruh on 20/12/16.
//


#include "display/GameScene.hpp"


std::mutex g_mutex;

GameScene::GameScene(SoundManager::MusicType type) :
        AScene(type),
        starfield(TextureManager::get(TextureManager::STARFIELD), TextureManager::get(TextureManager::STARFIELD), 250),
        starfieldParallax(TextureManager::get(TextureManager::STARFIELD), TextureManager::get(TextureManager::STARFIELD), 570)
{
    starfield.setSize(WIN_X, WIN_Y);
    starfieldParallax.setSize(WIN_X, WIN_Y);

    this->font.loadFromFile("assets/rtype_font.ttf");

    this->pressEscapeInfo.setFont(this->font);
    this->pressEscapeInfo.setCharacterSize(50);
    this->pressEscapeInfo.setString("Press ESCAPE to continue");
    sf::FloatRect   rect = this->pressEscapeInfo.getLocalBounds();
    this->pressEscapeInfo.setPosition(WIN_X / 2.0f - rect.width / 2.0f, WIN_Y / 4.0f * 3.0f - rect.height * 1.6f);
    this->pressEscapeInfo.setColor(sf::Color(138, 212, 241, 255));

    this->gameResult.setFont(this->font);
    this->gameResult.setCharacterSize(180);
    this->gameResult.setString("UNDEFINED");
    rect = this->gameResult.getGlobalBounds();
    this->gameResult.setPosition(WIN_X / 2.0f - rect.width / 2.0f, WIN_Y / 2.0f - rect.height * 1.6f);
    this->gameResult.setColor(sf::Color(138, 212, 241, 255));

    this->hasEnded = false;
}

void GameScene::useEntityPos(const EntityPos &entityPos)
{
//    std::cout << entityPos << std::endl;
    g_mutex.lock();
    if (entityPos.getType() == ENTITY_POS)
    {
        if (this->entities.find(entityPos.idGen) == this->entities.end())
        {
            this->entities[entityPos.idGen] = ObjectPool::Instance().getObject(
                    static_cast<EntityType>(entityPos.idDesc));
            this->entities[entityPos.idGen]->reset();
            this->entities[entityPos.idGen]->playSound();
        }
    }
    else if (entityPos.getType() == DEATH_ENTITY)
    {
        if (this->entities.find(entityPos.idGen) != this->entities.end())
            ObjectPool::Instance().returnObject(this->entities[entityPos.idGen]);
        this->entities[entityPos.idGen] = ObjectPool::Instance().getObject(static_cast<EntityType>(entityPos.idDesc));
        this->entities[entityPos.idGen]->reset();
        this->entities[entityPos.idGen]->playSound();
    }
    AEntity *instance = this->entities[entityPos.idGen];
    instance->setPosition(entityPos.x * WIN_X / 100, entityPos.y * WIN_Y / 100);
    instance->setDirection(entityPos.xDir * WIN_X / 100, entityPos.yDir * WIN_X / 100);
    g_mutex.unlock();
}

void GameScene::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    (void)states;
    target.draw(this->starfieldParallax);
    target.draw(this->starfield);

    for (auto it = this->entities.begin(); it != this->entities.end() ; it++)
    {
        if (it->second != nullptr)
            target.draw(*(it->second));
    }
    if (this->hasEnded)
    {
        target.draw(this->gameResult);
        target.draw(this->pressEscapeInfo);
    }
}

void GameScene::update(float deltaTime)
{
    starfield.update(deltaTime);
    starfieldParallax.update(deltaTime);

    g_mutex.lock();
    for (auto it = this->entities.begin(); it != this->entities.end() ; it++)
    {
        if (!it->second->isDone(WIN_X, WIN_Y))
            it->second->update(deltaTime);
        else
        {
            ObjectPool::Instance().returnObject(it->second);
            it = this->entities.erase(it);
            if (it == this->entities.end())
                break;
        }
    }
    g_mutex.unlock();
}

void  GameScene::useButtonEvent(const ButtonEvent &buttonEvent)
{
    if (buttonEvent.getButtonType() == ESCAPE)
    {
        g_mutex.lock();
        while (!this->entities.empty())
        {
            ObjectPool::Instance().returnObject(this->entities.begin()->second);
            this->entities.erase(this->entities.begin());
        }
        g_mutex.unlock();
        setActive(false);
        if (this->links.find(CHOOSE_GAME) != this->links.end())
            this->links[CHOOSE_GAME]->setActive(true);
        Core::getInstance().sendLeaveGame();
    }
}

void GameScene::useGameResult(const SimpleInfo &result)
{
    this->hasEnded = true;
    if (result.getType() == GAME_WON)
        this->gameResult.setString("VICTORY");
    else if (result.getType() == GAME_LOST)
        this->gameResult.setString("DEFEAT");
    else
        this->hasEnded = false;
}

void GameScene::setActive(bool value)
{
    AScene::setActive(value);
    this->hasEnded = false;
}