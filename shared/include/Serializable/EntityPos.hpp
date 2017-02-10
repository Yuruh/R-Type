//
// Created by ossalag on 12/12/16.
//

#ifndef     RTYPE_ENTITYPOS_PACKET_HPP
# define    RTYPE_ENTITYPOS_PACKET_HPP

# include "ASerializable.hpp"

struct       EntityPos : public ASerializable {
public:
    EntityPos();
    EntityPos(PacketType);
    ~EntityPos();

    std::string           serialize() const;
    void            operator<<(const char*);
    ISerializable*        clone() const;

    unsigned int    idDesc;
    unsigned int    idGen;
    float           x;
    float           y;
    float           xDir;
    float           yDir;
    bool            firstPlan;
};

std::ostream&       operator<<(std::ostream &os, const EntityPos&);

#endif //RTYPE_ENTITYPOS_HPP
