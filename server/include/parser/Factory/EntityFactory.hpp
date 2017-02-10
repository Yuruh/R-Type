//
// Created by wasta-geek on 06/12/16.
//

#ifndef SERVER_ENTITYFACTORY_HPP
#define SERVER_ENTITYFACTORY_HPP

#include <map>
#include <string>
#include "ANonPlayable.hpp"

class EntityFactory
{
    EntityFactory();
public:
    ~EntityFactory();
    static const EntityFactory    *getInstance();

    template <typename Type>
    static ANonPlayable *newEntity();
    static ANonPlayable* createEntity(EntityType , unsigned int);
    static ANonPlayable * createEntity(EntityType, unsigned int, bool);
    ANonPlayable * createInitializedEntity(EntityType, std::map<std::string, float> &) const;
    static unsigned int newEntityID();
};


#endif //SERVER_ENTITYFACTORY_HPP
