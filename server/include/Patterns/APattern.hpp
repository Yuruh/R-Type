//
// Created by wasta-geek on 06/12/16.
//

#ifndef SHARED_APATTERN_HPP
#define SHARED_APATTERN_HPP

#include <utility>
#include "Pattern.hpp"

class APattern {
protected:
    Pattern::type _type;
    std::pair<float, float> _dir;
public:
    virtual ~APattern();

    virtual void update() {}

    std::pair<float, float> const &getDirection() const;

    Pattern::type getType() const;
};


#endif //SHARED_APATTERN_HPP
