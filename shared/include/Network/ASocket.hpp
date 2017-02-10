//
// Created by yuruh on 07/12/16.
//

#ifndef RTYPE_ASOCKET_HPP
#define RTYPE_ASOCKET_HPP

#include "ISocket.hpp"
#ifdef __linux__ 
#include <sys/socket.h>
#include <netdb.h>
//#define INVALID_SOCKET -1
//typedef int SOCKET
//linux code goes here
#elif _WIN32	
#include <WinSock2.h>
#include <BaseTsd.h>
typedef uint32_t in_addr_t;
typedef SSIZE_T ssize_t;
// windows code goes here
#endif
#include <stdexcept>

class ASocket : public ISocket {
protected:
    int         socket_fd;
    int         socket_id;
    std::string buffer;

    in_addr_t       addr = 0;
    uint16_t        port = 0;
    char            *ip = nullptr;

    void            fillInfo();

public:
    ASocket() : socket_fd(-1), socket_id(-1) {}

    ASocket(int fd) : socket_fd(fd), socket_id(-1) {}

    virtual bool init()= 0;

    virtual std::vector<uint32_t> doAccept() = 0;

    void doSend(std::string const &);

    std::string doRecv();

    std::string doRecvFrom();

    bool doConnect(std::string const &hostname, uint16_t port);

    bool doBind(uint16_t port);

    bool doListen();

    int getFd() const { return (this->socket_fd); }

    int getId() const { return (this->socket_id); }

    void setId(int id) { this->socket_id = id; }

    uint32_t    getAddr();

    uint16_t    getPort();

    char        *getIp();

    static void    packetize(std::string &buffer, uint32_t clientFd);
};


#endif //RTYPE_ASOCKET_HPP
