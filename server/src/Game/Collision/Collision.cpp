//
// Created by ossalag on 11/12/16.
//

#include <iostream>
#include "Collision.hpp"

Collision::Collision() {
    std::cout << "New Collision" << std::endl;
}

Collision::~Collision() {

}

uint32_t Collision::getPlayerId() const {
    return this->_playerId;
}

void Collision::setPlayerId(uint32_t playerId) {
    this->_playerId = playerId;
    std::cout << "Player ID [" << this->_playerId << "]" << std::endl;
}

std::pair<float, float> const &Collision::getPlayerPos() const {
    return this->_playerPos;
}

void Collision::setPlayerPos(float x, float y) {
    this->_playerPos = std::pair<float, float>(x, y);
}

void Collision::setPlayerPos(std::pair<float, float> playerPos) {
    this->_playerPos = playerPos;
}

std::pair<uint32_t, uint32_t> const &Collision::getEntityId() const {
    return this->_entityId;
}

void Collision::setEntityId(uint32_t type, uint32_t id) {
    this->_entityId = std::pair<uint32_t, uint32_t>(type, id);
    std::cout << "Entity ID [" << this->_entityId.first << ", " << this->_entityId.second << "]" << std::endl;
}

void Collision::setEntityId(std::pair<uint32_t, uint32_t> entityId) {
    this->_entityId = entityId;
}

std::pair<float, float> Collision::getEntityPos() const {
    return this->_entityPos;
}

void Collision::setEntityPos(float x, float y) {
    this->_entityPos = std::pair<float, float>(x, y);
}

void Collision::setEntityPos(std::pair<float, float> entityPos) {
    this->_entityPos = entityPos;
}