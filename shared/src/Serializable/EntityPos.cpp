//
// Created by ossalag on 12/12/16.
//

#include "Serializable/EntityPos.hpp"

EntityPos::EntityPos() {
    this->_type = ENTITY_POS;
    this->idDesc = 0;
    this->idGen = 0;
    this->x = 0;
    this->y = 0;
    this->xDir = 0;
    this->yDir = 0;
    this->firstPlan = true;
}

EntityPos::EntityPos(PacketType type) {
    this->_type = type;
    this->idDesc = 0;
    this->idGen = 0;
    this->x = 0;
    this->y = 0;
    this->xDir = 0;
    this->yDir = 0;
    this->firstPlan = true;
}

EntityPos::~EntityPos() {

}

std::string EntityPos::serialize() const {
    size_t          i = 0;
    unsigned int    lenData = sizeof(this->idDesc) + sizeof(this->idGen) + sizeof(this->x) +
                    sizeof(this->y) + sizeof(this->xDir) + sizeof(this->yDir) + sizeof(this->firstPlan);
    char*           data = new char[sizeof(this->_type) + sizeof(lenData) + lenData];
    std::string     ret;

    memcpy(data + i, &(this->_type), sizeof(this->_type));
    i += sizeof(this->_type);
    memcpy(data + i, &lenData, sizeof(lenData));
    i += sizeof(lenData);
    memcpy(data + i, &(this->idDesc), sizeof(this->idDesc));
    i += sizeof(this->idDesc);
    memcpy(data + i, &(this->idGen), sizeof(this->idGen));
    i += sizeof(this->idGen);
    memcpy(data + i, &(this->x), sizeof(this->x));
    i += sizeof(this->x);
    memcpy(data + i, &(this->y), sizeof(this->y));
    i += sizeof(this->y);
    memcpy(data + i, &(this->xDir), sizeof(this->xDir));
    i += sizeof(this->xDir);
    memcpy(data + i, &(this->yDir), sizeof(this->yDir));
    i += sizeof(this->yDir);
    memcpy(data + i, &(this->firstPlan), sizeof(this->firstPlan));
    i += sizeof(this->firstPlan);

    ret.assign(data, i);
    delete[] data;
    return (ret);
}

void EntityPos::operator<<(const char* bytes)
{
    size_t  it = 0;
    size_t  len;

    this->_type = this->parseType<PacketType>(bytes, it);
    it += 4;
    len = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->idDesc = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->idGen = this->parseType<uint32_t>(bytes, it);
    it += 4;
    this->x = this->parseType<float>(bytes, it);
    it += 4;
    this->y = this->parseType<float>(bytes, it);
    it += 4;
    this->xDir = this->parseType<float>(bytes, it);
    it += 4;
    this->yDir = this->parseType<float>(bytes, it);
    it += 4;
    this->firstPlan = static_cast<bool>(bytes[it]);
}

ISerializable*        EntityPos::clone() const {
    ISerializable*    clone = new EntityPos(this->_type);

    return (clone);
}

std::ostream&       operator<<(std::ostream &os, const EntityPos &entity) {
    os << "idDesc = " << entity.idDesc << std::endl;
    os << "idGen = " << entity.idGen << std::endl;
    os << "x = " << entity.x << std::endl;
    os << "y = " << entity.y << std::endl;
    os << "xDir = " << entity.xDir << std::endl;
    os << "yDir = " << entity.yDir << std::endl;
    os << "first_plan = " << entity.firstPlan << std::endl;
    return (os);
}
