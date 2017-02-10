//
// Created by wasta-geek on 08/12/16.
//

#ifndef SERVER_MONSTERCREATOR_HPP
#define SERVER_MONSTERCREATOR_HPP

#include <map>
#include <Monsters/EnemyShip.hpp>
#include <Monsters/Taz.hpp>
#include "EntityFactory.hpp"
#include "Monsters/Brainfart.hpp"

void buildMonsterType();

struct MonsterCreator
{
public:
    static std::map<EntityType , ANonPlayable*(*)()> _creator;
    static ANonPlayable *create(EntityType typeToCreate)
    {
        static bool test = true;

        if (test) {
            buildMonsterType();
            test = false;
        }
        std::map<EntityType , ANonPlayable *(*)()>::iterator elem = MonsterCreator::_creator.find(typeToCreate);
        if (elem != _creator.end())
            return elem->second();
        return NULL;
    }

};

std::map<EntityType, ANonPlayable*(*)()> MonsterCreator::_creator;

void buildMonsterType()
{
    MonsterCreator::_creator.insert(std::make_pair(BRAINFART, &EntityFactory::newEntity<Brainfart>));
    MonsterCreator::_creator.insert(std::make_pair(ENEMY_SHIP, &EntityFactory::newEntity<EnemyShip>));
    MonsterCreator::_creator.insert(std::make_pair(TAZ, &EntityFactory::newEntity<Taz>));
}

#endif //SERVER_MONSTERCREATOR_HPP
