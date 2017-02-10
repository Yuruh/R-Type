//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_ISOCKET_HPP
#define RTYPE_ISOCKET_HPP

#include <string>
#include <vector>

class ISocket {
public:
    virtual bool init()= 0;

    virtual bool doConnect(std::string const &, uint16_t)= 0;

    virtual bool doBind(uint16_t) = 0;

    virtual bool doListen() = 0;

    virtual std::vector<uint32_t> doAccept() = 0;

    virtual void doSend(std::string const &)= 0;

    virtual std::string doRecv()= 0;

    virtual std::string doRecvFrom()= 0;

    virtual int getFd() const = 0;

    virtual int getId() const = 0;

    virtual void setId(int id) = 0;

    virtual uint32_t    getAddr() = 0;

    virtual char        *getIp() = 0;

    virtual uint16_t    getPort() = 0;
};

#endif //RTYPE_ASOCKET_HPP
