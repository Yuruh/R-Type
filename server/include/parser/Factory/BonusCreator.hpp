//
// Created by wasta-geek on 10/12/16.
//

#ifndef SERVER_RTYPE_BONUSCREATOR_HPP
#define SERVER_RTYPE_BONUSCREATOR_HPP

#include <map>
#include "EntityFactory.hpp"

void buildBonusType();

struct BonusCreator
{
public:
    static std::map<EntityType, ANonPlayable*(*)()> _creator;
    static ANonPlayable * create(EntityType typeToCreate)
    {
        static bool test = true;

        if (test) {
            buildBonusType();
            test = false;
        }
        std::map<EntityType , ANonPlayable *(*)()>::iterator elem = BonusCreator::_creator.find(typeToCreate);
        if (elem != _creator.end())
            return elem->second();
        return NULL;
    }

};

std::map<EntityType, ANonPlayable*(*)()> BonusCreator::_creator;

void buildBonusType()
{
//    BonusCreator::_creator.insert(std::make_pair(SPEED_BONUS, &EntityFactory::newEntity<Brainfart>));
}

#endif //SERVER_RTYPE_BONUSCREATOR_HPP
