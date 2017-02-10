//
// Created by wasta-geek on 06/12/16.
//

#include <iostream>
#include <utility>
#include <AMonster.hpp>
#include "Convertor.hpp"
#include "Brainfart.hpp"
#include <Simulation.hpp>
#include "Factory/MonsterCreator.hpp"
#include "Factory/BonusCreator.hpp"
#include "Factory/BackgroundDecorativeCreator.hpp"
#include "Factory/ForegroundDecorativeCreator.hpp"
#include "Exception/FactoryException.hpp"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

const EntityFactory *EntityFactory::getInstance()
{
    static EntityFactory _instance;

    return &_instance;
}

template <typename Type>
ANonPlayable* EntityFactory::newEntity()
{
    return new Type;
}

ANonPlayable* EntityFactory::createEntity(EntityType entityType, unsigned int id)
{
    if (entityType == BONUS) {
        if (id <= BONUS || id >= END_BONUS)
            throw FactoryException("Cannot create a Bonus with a wrong Id");
        return BonusCreator::create(static_cast<EntityType>(id));
    }
    else if (entityType == MONSTERS) {
        if (id <= MONSTERS || id >= END_MONSTERS)
            throw FactoryException("Cannot create a Monster with a wrong Id");
        return MonsterCreator::create(static_cast<EntityType >(id));
    }
    return 0;
}

ANonPlayable * EntityFactory::createEntity(EntityType type, unsigned int id, bool firstPlan)
{
    if (firstPlan) {
        if (id <= FOREGROUND_DECORATIVE || id >= END_FOREGROUND_DECORATIVE)
            throw FactoryException("Cannot create a ForegroundDecorative with a wrong Id");
        return ForegroundDecorativeCreator::create(static_cast<EntityType >(id));
    } else {
        if (id <= BACKGROUND_DECORATIVE || id >= END_BACKGROUND_DECORATIVE)
            throw FactoryException("Cannot create a BackgroundDecorative with a wrong Id");
        return BackgroundDecorativeCreator::create(static_cast<EntityType >(id));
    }
}

ANonPlayable * EntityFactory::createInitializedEntity(EntityType type, std::map<std::string, float> &contents) const
{
    auto idIterator = contents.find("id");
    if (idIterator == contents.end())
        throw FactoryException("Cannot create an Entity without Id in Factory");
    float id = idIterator->second;

    bool firstPlan = true;

    if (type == FOREGROUND_DECORATIVE || type == BACKGROUND_DECORATIVE) {
        auto firstPlanIterator = contents.find("firstplan");
        if (firstPlanIterator == contents.end())
            throw FactoryException("Cannot create a decorative Entity without firstPlan in Factory");
        if (firstPlanIterator->second != 0 || firstPlanIterator->second != 1)
            throw FactoryException("Cannot create a decorative Entity without a valid type in Factory");
        firstPlan = static_cast<bool>(firstPlanIterator->second);
    }

    ANonPlayable *ret = (type == FOREGROUND_DECORATIVE || type == BACKGROUND_DECORATIVE)
                   ? EntityFactory::createEntity(type, (unsigned int) id, firstPlan)
                   : EntityFactory::createEntity(type, (unsigned int) id);

    if (!ret)
        return NULL;

    auto xIterator = contents.find("x");
    auto yIterator = contents.find("y");

    if (xIterator == contents.end())
        throw FactoryException("Cannot create an Entity without a x position");
    if (yIterator == contents.end())
        throw FactoryException("Cannot create an Entity without a y position");

    if (xIterator->second < -20 || xIterator->second > 120)
        throw FactoryException("Cannot create an Entity without a x position which is not a percentage");
    if (yIterator->second < -20 || yIterator->second > 120)
        throw FactoryException("Cannot create an Entity with a y position which is not a percentage");

    float xPosition = Convertor::toRelativeServer(xIterator->second, 'x');
    float yPosition = Convertor::toRelativeServer(yIterator->second, 'y');

    ret->setX(xPosition - ret->getBoundingBoxes()[0].offsetX / 2);
    ret->setY(yPosition - ret->getBoundingBoxes()[0].offsetY / 2);

    float speed = 1;
    float size = 1;
    auto sizeIterator = contents.find("size");
    auto speedIterator = contents.find("speed");

    if (sizeIterator != contents.end())
        if (sizeIterator->second < 0 || sizeIterator->second > 1)
            throw FactoryException("Cannot create an Entity with a sizeScale which is not between 0 and 1");
        else
            size = sizeIterator->second;
    if (speedIterator != contents.end())
        if (speedIterator->second < 0 || speedIterator->second > 1)
            throw FactoryException("Cannot create an Entity with a speedScale which is not between 0 and 1");
        else
            speed = speedIterator->second;
    ret->setSizeScale(size);
    ret->setSpeedScale(speed);

    auto patternIterator = contents.find("pattern");
    float pattern = 0;

    if (patternIterator != contents.end()) {
        if (patternIterator->second < 0 || patternIterator->second > 7)
            throw FactoryException("Cannot create an Entity with a pattern which is not between 0 and 7");
        else
            pattern = patternIterator->second;
    }
    ret->setPattern((Pattern::type)((uint32_t )pattern));

    return ret;
}

unsigned int EntityFactory::newEntityID()
{
    static unsigned int uniqueID = 0;

    return uniqueID++;
}
