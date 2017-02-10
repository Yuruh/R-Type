//
// Created by wasta-geek on 10/12/16.
//

#ifndef SERVER_RTYPE_BACKGROUNDDECORATIVECREATOR_HPP
#define SERVER_RTYPE_BACKGROUNDDECORATIVECREATOR_HPP

#include <map>
#include "EntityFactory.hpp"

void buildBackgroundDecorativeType();

struct BackgroundDecorativeCreator
{
public:
    static std::map<EntityType, ANonPlayable*(*)()> _creator;
    static ANonPlayable * create(EntityType typeToCreate)
    {
        static bool test = true;

        if (test) {
            buildBackgroundDecorativeType();
            test = false;
        }
        std::map<EntityType, ANonPlayable *(*)()>::iterator elem = BackgroundDecorativeCreator::_creator.find(typeToCreate);
        if (elem != _creator.end())
            return elem->second();
        return NULL;
    }

};

std::map<EntityType, ANonPlayable*(*)()> BackgroundDecorativeCreator::_creator;

void buildBackgroundDecorativeType()
{
//    BackgroundDecorativeCreator::_creator.insert(std::make_pair(BackgroundDecorative::SPACE, &EntityFactory::newEntity<Space>));
}

#endif //SERVER_RTYPE_BACKGROUNDDECORATIVECREATOR_HPP
