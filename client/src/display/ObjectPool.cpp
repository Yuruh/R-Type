//
// Created by yuruh on 09/12/16.
//

#include <iostream>
#include "display/ObjectPool.hpp"
#include "display/TileSetSprites.hpp"
#include "display/PlayerSprites.hpp"

ObjectPool      ObjectPool::_instance = ObjectPool();

ObjectPool::ObjectPool()
{

}

ObjectPool::~ObjectPool()
{
    for (auto it = this->objects.begin(); it != this->objects.end() ; ++it)
    {
        auto queue = it->second;
        while (!queue.empty())
        {
            delete queue.front();
            queue.pop();
        }
    }
    this->objects.clear();
}

AEntity *ObjectPool::getObject(EntityType entity)
{
    if (!objects[entity].empty())
    {
        AEntity *instance = objects[entity].front();
        objects[entity].pop();
        return instance;
    }
    else
    {
        if (entity >= PLAYER1 && entity <= PLAYER4)
            return new PlayerSprites(entity);
        else
            return new TileSetSprites(entity);
    }
}

void ObjectPool::returnObject(AEntity *instance)
{
    this->objects[instance->getName()].push(instance);
}

ObjectPool &ObjectPool::Instance()
{
    return _instance;
}
