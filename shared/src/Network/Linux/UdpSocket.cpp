//
// UdpSocket.cpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/shared/src/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Thu Dec 15 21:25:37 2016 Raphael Thiebault
// Last update Sun Dec 25 23:08:52 2016 Antoine Lempereur
//

#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include "UdpSocket.hpp"

UdpSocket::UdpSocket() : ASocket() {
    if (!this->init())
        throw std::exception();
}


UdpSocket::~UdpSocket() {
    close(this->socket_fd);
}

bool UdpSocket::init() {
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    return (this->socket_fd != -1);
}

std::vector<uint32_t> UdpSocket::doAccept() {
    struct sockaddr_in new_in;

    char buf[1024];
    ssize_t ret;
    socklen_t size = sizeof(new_in);

    if ((ret = recvfrom(this->socket_fd, buf, 1024 - 1, 0, (struct sockaddr *) &new_in, &size)) <= 0)
        return (std::vector<uint32_t>());
    // perror("RecvFrom: ");

    buf[ret] = '\0';

    this->buffer.assign(buf, (unsigned long) ret);
    return (std::vector<uint32_t>({ new_in.sin_addr.s_addr, htons(new_in.sin_port) }));
}
