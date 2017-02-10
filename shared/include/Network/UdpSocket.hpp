//
// UdpSocket.hpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/shared/include/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Thu Dec 15 21:16:08 2016 Raphael Thiebault
// Last update Sun Dec 18 12:50:41 2016 Raphael Thiebault
//

#pragma once

#include <vector>
#include <map>
#include "ASocket.hpp"

class UdpSocket : public ASocket {
public:
    UdpSocket();

    ~UdpSocket();

    bool init();

    std::vector<uint32_t> doAccept();
};
