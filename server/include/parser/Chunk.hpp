//
// Created by wasta-geek on 06/12/16.
//

#ifndef RTYPE_ACHUNK_HPP
#define RTYPE_ACHUNK_HPP

#include <Entities/ANonPlayable.hpp>
#include "IChunk.hpp"

class Chunk : public IChunk
{
protected:
    std::vector<ANonPlayable*>    	_contents;
    int            			 		_id;
public:
    Chunk();
    ~Chunk();

    virtual std::vector<ANonPlayable*> 	getContents();
    virtual int 					getId();
   	void 							addContents(ANonPlayable*);

};

#endif //RTYPE_ACHUNK_HPP
