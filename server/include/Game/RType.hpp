//
// Created by ossalag on 14/12/16.
//

#ifndef SERVER_RTYPE_RTYPE_HPP
#define SERVER_RTYPE_RTYPE_HPP

#include "Game/AGame.hpp"
#include "RTypeParser.hpp"
#include "Simulation.hpp"

class   RType : public AGame {
public:
    RType(uint32_t id);
    ~RType();

    virtual void joystickUsed(float, float, uint32_t);
    virtual void startGame();
    virtual bool isLevelOver();
    virtual bool isGameOver();
    virtual bool isGameEmpty();
    virtual void update(float);

    void useButtonEvent(const ButtonEvent &buttonEvent, uint32_t i);
    void useJoystickEvent(const JoystickEvent &joystickEvent, uint32_t);

    Simulation  simulator;
private:
    RTypeParser         *_parser;
    std::vector<EntityType > _availableID;

    void disconnectPlayer(uint32_t playerId);
};

#endif //SERVER_RTYPE_RTYPE_HPP
