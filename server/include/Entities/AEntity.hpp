//
// Created by wasta-geek on 06/12/16.
//

#ifndef SHARED_AENTITY_HPP
#define SHARED_AENTITY_HPP

#include <string>
#include <EntityType.hpp>
#include <vector>
#include <Game/Collision/BoundingBox.hpp>
#include "APattern.hpp"
#include "Types/Pattern.hpp"

class AEntity {
public:
    AEntity();

    virtual ~AEntity();

    void setX(float);
    void setY(float);

    const float &getX() const;
    const float &getY() const;

    const float &getSpeedScale() const;
    void setSpeedScale(float);

    const float &getSizeScale() const;
    void setSizeScale(float);

    virtual const std::pair<float, float> & getDirection() const = 0;
    virtual void setPosition(float x, float y);

    const EntityType &getCategory() const;
    void setCategory(EntityType);

    uint32_t getId() const;
    void setId(uint32_t id);

    bool isFirstPlan() const;

    void moveX(float);
    void moveY(float);

    const std::vector<BoundingBox> &getBoundingBoxes() const;

protected:
    float _x;
    float _y;
    float _sizeScale;
    float _speedScale;
    unsigned int _id;
    EntityType _category;
    bool _firstPlan;
    std::vector<BoundingBox>    _boundingBoxes;
};


#endif //SHARED_AENTITY_HPP
