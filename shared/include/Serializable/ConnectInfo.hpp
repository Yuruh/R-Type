//
// Created by yuruh on 19/12/16.
//

#ifndef SHARED_CONNECTINFO_HPP
#define SHARED_CONNECTINFO_HPP


#include "ASerializable.hpp"

struct ConnectInfo : public ASerializable
{
public:
    ConnectInfo();
    ~ConnectInfo();


    std::string     serialize() const;
    void            operator<<(const char*);
    ISerializable* 		clone() const;

    uint16_t        port;
};

std::ostream&       operator<<(std::ostream &os, const ConnectInfo&);

#endif //SHARED_CONNECTINFO_HPP
