//
// Created by ossalag on 15/12/16.
//

#include <iostream>
#include "Player.hpp"
#include <Game/Simulation/Simulation.hpp>
#include <Missiles/StandardMissile.hpp>
#include <Missiles/WaveMissile.hpp>
#include "Convertor.hpp"

Player::Player() : APlayable()
{
    this->_x = Convertor::toRelativeServer(SPAWN_X, 'x');
    this->_y = Convertor::toRelativeServer(SPAWN_Y, 'y');

    this->_hp = HP;
    BoundingBox box;

    this->_category = PLAYER1;
    box.x = 0;
    box.y = 0;
    box.offsetX = PLAYER_SIZE * SERVER_Y / 100;
    box.offsetY = PLAYER_SIZE * SERVER_Y / 100;
    this->_boundingBoxes.push_back(box);

    this->shootCd = SHOOT_COOLDOWN;
    this->waveCd = WAVE_COOLDOWN / 2;
}

Player::~Player()
{

}

void    Player::handleMovement(float deltaTime)
{
    float   movingValue = (PLAYER_SPEED * deltaTime);

    float x = 0;
    float y = 0;

    if (joystickX > 0.1 || joystickX < -0.1 || joystickY > 0.1 || joystickY < -0.1)
    {
        x = (float) (joystickX / 100.0 * movingValue);
        y = (float) (joystickY / 100.0 * movingValue);
    }
    else
    {
        if ((this->events[Z] || this->events[UP]))
            y -= movingValue;
        if ((this->events[S] || this->events[DOWN]))
            y += movingValue;
        if ((this->events[Q] || this->events[LEFT]))
            x -= movingValue;
        if ((this->events[D] || this->events[RIGHT]))
            x += movingValue;
    }
    if (x != 0)
    if (this->_x < SERVER_X - x - this->getBoundingBoxes()[0].offsetX * 2 && this->_x + x > 10)
        this->moveX(x);
    if (this->_y < SERVER_Y - y - this->getBoundingBoxes()[0].offsetY * 2 && this->_y + y > 10)
        this->moveY(y);
    this->_dir = std::pair<float, float>(x, y);
}

void Player::update(float deltaTime, std::vector<AMissile *> &missiles)
{
    this->shootCd += deltaTime;
    this->waveCd += deltaTime;
	this->handleMovement(deltaTime);

    if (this->events[SPACE] && this->shootCd >= SHOOT_COOLDOWN)
    {
        AMissile *missile = new StandardMissile();
        missile->setX(this->_x + PLAYER_SIZE / 2 * SERVER_X / 100);
        missile->setY(this->_y + PLAYER_SIZE / 2 * SERVER_Y / 100);

        missiles.push_back(missile);
        this->shootCd = 0;
    }
    if (this->events[RETURN] && this->waveCd >= WAVE_COOLDOWN)
    {
        float x = this->_x + PLAYER_SIZE / 2.0f * SERVER_X / 100.0f;
        float y = this->_y + PLAYER_SIZE / 2.0f * SERVER_Y / 100.0f;

        missiles.push_back(new WaveMissile(x, y, 1.0f, 1.0f));
        missiles.push_back(new WaveMissile(x, y, 1.0f, 0.6f));
        missiles.push_back(new WaveMissile(x, y, 1.0f, 0.2f));
        missiles.push_back(new WaveMissile(x, y, 1.0f, -0.2f));
        missiles.push_back(new WaveMissile(x, y, 1.0f, -0.6f));
        missiles.push_back(new WaveMissile(x, y, 1.0f, -1.0f));

        this->waveCd = 0;
    }
    this->resetEvents();
}