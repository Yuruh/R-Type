//
// Created by wasta-geek on 06/12/16.
//

#include <parser/Factory/EntityFactory.hpp>


AEntity::AEntity()
{
    this->_id = EntityFactory::newEntityID();
    this->_firstPlan = 1;
    this->_sizeScale = 1;
    this->_speedScale = 1;
    this->_x = 0;
    this->_y = 0;
    this->_category = UNDEFINED_ENTITY;
}

AEntity::~AEntity() {}

unsigned int AEntity::getId() const {
    return this->_id;
}

void AEntity::setId(uint32_t id) {
    this->_id = id;
}

const float &AEntity::getX() const {
    return this->_x;
}

void AEntity::setX(float newXPosition) {
    this->_x = newXPosition;
}

const float &AEntity::getY() const {
    return this->_y;
}

void AEntity::setY(float newYPosition) {
    this->_y = newYPosition;
}

const float &AEntity::getSpeedScale() const {
    return this->_speedScale;
}

void AEntity::setSpeedScale(float newSpeedScale) {
    this->_speedScale = newSpeedScale;
}

const float &AEntity::getSizeScale() const {
    return this->_sizeScale;
}

void AEntity::setSizeScale(float newSizeScale) {
    this->_sizeScale = newSizeScale;
}

void AEntity::setPosition(float x, float y) {
    this->_x = x;
    this->_y = y;
}

const EntityType &AEntity::getCategory() const {
    return this->_category;
}

bool AEntity::isFirstPlan() const {
    return _firstPlan;
}

void AEntity::setCategory(EntityType category)
{
    this->_category = category;
}

void AEntity::moveX(float x)
{
    this->_x += x;
}

void AEntity::moveY(float y)
{
    this->_y += y;
}

const std::vector<BoundingBox> &AEntity::getBoundingBoxes() const
{
    return _boundingBoxes;
}