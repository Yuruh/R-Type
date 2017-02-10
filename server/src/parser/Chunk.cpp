//
// Created by wasta-geek on 06/12/16.
//


#include <parser/Chunk.hpp>

Chunk::Chunk()
{
    this->_id = -1;
}

Chunk::~Chunk()
{

}

std::vector<ANonPlayable*> Chunk::getContents()
{
    return this->_contents;
}

int Chunk::getId()
{
    return this->_id;
}

void 					Chunk::addContents(ANonPlayable *entity) {
	this->_contents.push_back(entity);
}