//
// Created by wasta-geek on 06/12/16.
//

#ifndef RTYPE_ICHUNK_HPP
#define RTYPE_ICHUNK_HPP

#include <vector>
#include "ANonPlayable.hpp"

class IChunk
{
public:
	virtual void 					addContents(ANonPlayable*) = 0;
    virtual std::vector<ANonPlayable*> 	getContents() = 0;
    virtual int 					getId() = 0;
    virtual 						~IChunk() {};
};

#endif //RTYPE_ICHUNK_HPP
