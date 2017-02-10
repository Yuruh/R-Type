//
// Created by yuruh on 09/12/16.
//

#ifndef RTYPE_OBJECTPOOL_HPP
#define RTYPE_OBJECTPOOL_HPP


#include "AEntity.hpp"
#include <queue>

class ObjectPool
{
private:
    std::map<EntityType, std::queue<AEntity*> > objects;
    static ObjectPool _instance;
    ObjectPool ();
    virtual ~ObjectPool();

public:
    AEntity*    getObject(EntityType);
    void        returnObject(AEntity*);
    static ObjectPool &Instance();
};


#endif //RTYPE_OBJECTPOOL_HPP
