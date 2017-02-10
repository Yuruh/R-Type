//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_TCPSOCKET_HPP
#define RTYPE_TCPSOCKET_HPP

#include "ASocket.hpp"

//#ifdef WIN32
//#include "WinSocket.hpp"
//class TcpSocket : public ASocket, public WinSocket
//#else
//#include "UnixSocket.hpp"
class TcpSocket : public ASocket//, public UnixSocket
//#endif
{
public:
    TcpSocket();

    TcpSocket(int);

    ~TcpSocket();

    bool	init();
    std::vector<uint32_t> doAccept();
};


#endif //RTYPE_TCPSOCKET_HPP
