//
// Created by wasta-geek on 22/12/16.
//

#ifndef SERVER_RTYPE_ANONPLAYABLE_HPP
#define SERVER_RTYPE_ANONPLAYABLE_HPP


#include "AEntity.hpp"

class ANonPlayable : public AEntity
{
public:
    ANonPlayable();
    virtual ~ANonPlayable();
    Pattern::type getPattern() const;
    void          setPattern(Pattern::type patternType);
    virtual const std::pair<float, float> &getDirection() const;

    void updatePattern();

protected:
    APattern *_pattern;
};


#endif //SERVER_RTYPE_ANONPLAYABLE_HPP
