//
// Created by yuruh on 20/12/16.
//

#ifndef RTYPE_GAMESCENE_HPP
#define RTYPE_GAMESCENE_HPP

#include <list>

#include <display/AScene.hpp>
#include <display/AEntity.hpp>
#include <display/Scrolling.hpp>
#include <display/TextureManager.hpp>
#include <display/ObjectPool.hpp>
#include <Interpreter/ChiefInterpreter.hpp>
#include <mutex>
#include <Core.hpp>

class GameScene : public AScene
{
public:
    GameScene(SoundManager::MusicType type);
    ~GameScene() {}
    virtual void update(float);
    virtual void useEntityPos(const EntityPos &entityPos);
private:
    Scrolling   starfield;
    Scrolling   starfieldParallax;
    std::map<unsigned int, AEntity*>       entities;
    virtual void    draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void useButtonEvent(const ButtonEvent &buttonEvent);

    sf::Text    gameResult;
    sf::Text    pressEscapeInfo;
    bool        hasEnded;

    sf::Font    font;

    void useGameResult(const SimpleInfo &result);

    void setActive(bool value);
};


#endif //RTYPE_GAMESCENE_HPP
