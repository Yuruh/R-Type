//
// Created by wasta-geek on 10/12/16.
//

#ifndef SERVER_RTYPE_FOREGROUNDDECORATIVECREATOR_HPP
#define SERVER_RTYPE_FOREGROUNDDECORATIVECREATOR_HPP

#include <map>
#include "EntityFactory.hpp"

void buildForegroundDecorativeType();

struct ForegroundDecorativeCreator
{
public:
    static std::map<EntityType, ANonPlayable*(*)()> _creator;
    static ANonPlayable * create(EntityType typeToCreate)
    {
        static bool test = true;

        if (test) {
            buildForegroundDecorativeType();
            test = false;
        }
        std::map<EntityType , ANonPlayable *(*)()>::iterator elem = ForegroundDecorativeCreator::_creator.find(typeToCreate);
        if (elem != _creator.end())
            return elem->second();
        return NULL;
    }

};

std::map<EntityType, ANonPlayable*(*)()> ForegroundDecorativeCreator::_creator;

void buildForegroundDecorativeType()
{
//    ForegroundDecorativeCreator::_creator.insert(std::make_pair(ForegroundDecorative::WALL, &EntityFactory::newEntity<Wall>));
}

#endif //SERVER_RTYPE_FOREGROUNDDECORATIVECREATOR_HPP
