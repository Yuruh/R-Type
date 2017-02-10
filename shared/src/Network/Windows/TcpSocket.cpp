//
// Created by yuruh on 30/11/16.
//

#include <cstdio>
#include <vector>
#include <iostream>
#include <io.h>
#include "TcpSocket.hpp"

TcpSocket::TcpSocket() : ASocket() {
    if (!this->init())
        throw std::runtime_error("Error while creating socket");
}

TcpSocket::TcpSocket(int socket) : ASocket(socket) {}

TcpSocket::~TcpSocket() {
    _close(this->socket_fd);
}

bool TcpSocket::init() {
    this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    return (this->socket_fd != -1);
}

std::vector<uint32_t> TcpSocket::doAccept() {
    int new_fd;

    if ((new_fd = accept(this->socket_fd, NULL, NULL)) == -1)
        return (std::vector<uint32_t>());
    return (std::vector<uint32_t>({(uint32_t) new_fd}));
}