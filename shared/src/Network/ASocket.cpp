//
// ASocket.cpp for rtype in /home/raphicci/Documents/TEK3-2016/CPP_AVANCE/rtype/shared/src/
//
// Made by Raphael Thiebault
// Login   <thieba_r@epitech.net>
//
// Started on  Sat Dec 17 20:22:07 2016 Raphael Thiebault
// Last update Mon Dec 19 16:16:58 2016 Antoine Lempereur
//

#include	<ChiefInterpreter.hpp>
#ifdef __linux__
#include <arpa/inet.h>
#elif _WIN32
#define MSG_NOSIGNAL 0
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WS2tcpip.h>
#endif
#include	"ASocket.hpp"

bool ASocket::doConnect(std::string const& hostname, uint16_t port)
{
  struct sockaddr_in	addr;
  struct hostent        *hostinfo = gethostbyname(hostname.c_str());

  if (hostinfo == NULL) return (false);

    addr.sin_addr = *(in_addr *) hostinfo->h_addr;
    addr.sin_port = htons((uint16_t) port);
    addr.sin_family = AF_INET;

  return (connect(this->socket_fd, (struct sockaddr *)&addr, sizeof(addr)) != -1);
}

bool ASocket::doBind(uint16_t port)
{
    struct sockaddr_in	addr;

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);

    return (bind(this->socket_fd, (struct sockaddr *)&addr, sizeof(addr)) != -1);
}

bool ASocket::doListen()
{
  return (listen(this->socket_fd, 128) != -1);
}


void ASocket::doSend(std::string const &data) {
    send(this->socket_fd, data.c_str(), data.size(), MSG_NOSIGNAL);
}

std::string ASocket::doRecv() {
    char buf[1024];
    ssize_t ret;
    std::string packet;

    if ((ret = recv(this->socket_fd, buf, 1024 - 1, 0)) <= 0)
        return (packet);
    buf[ret] = '\0';

    packet.assign(buf, (unsigned long) ret);
    return (packet);
}

std::string ASocket::doRecvFrom() {
    std::string sending;

    sending = this->buffer;
    this->buffer.clear();
    return (sending);
}

//Recursively consume buffer
void ASocket::packetize(std::string &buffer, uint32_t clientId)
{
    uint32_t headerSize = sizeof(PacketType) + sizeof(uint32_t);
    if (buffer.size() >= headerSize)
    {
        PacketType value;
        uint32_t len;
        uint32_t packetLen;

        memcpy(&value, buffer.data(), sizeof(PacketType));
        if (value > UNDEFINED)
            return;
        memcpy(&len, buffer.data() + sizeof(PacketType), sizeof(uint32_t));
        packetLen = len + headerSize;
        if (buffer.size() >= packetLen && packetLen > 0)
        {
            ChiefInterpreter::getInstance().interpretPacket(buffer.substr(0, packetLen).data(), value, clientId);
            buffer.erase(0, packetLen);
            ASocket::packetize(buffer, clientId);
        }
    }
}

void        ASocket::fillInfo() {
    struct sockaddr_in sin;
    socklen_t addrlen = sizeof(sin);

    if (getsockname(this->socket_fd, (struct sockaddr *) &sin, &addrlen) == 0 &&
        sin.sin_family == AF_INET && addrlen == sizeof(sin)) {
        this->port = htons(sin.sin_port);
    }
    if (getpeername(this->socket_fd, (struct sockaddr *) &sin, &addrlen) == 0 &&
        sin.sin_family == AF_INET && addrlen == sizeof(sin)) {
        this->addr = sin.sin_addr.s_addr;
        this->ip = inet_ntoa(sin.sin_addr);
    }
}

uint32_t    ASocket::getAddr() {
    if (!this->addr)
        this->fillInfo();
    return (this->addr);
}

uint16_t    ASocket::getPort() {

    if (!this->port)
        this->fillInfo();
    return (this->port);
}

char        *ASocket::getIp() {
    if (!this->ip)
        fillInfo();
    return (this->ip);
}
