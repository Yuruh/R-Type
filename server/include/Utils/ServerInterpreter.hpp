//
// Created by yuruh on 15/12/16.
//

#ifndef SERVER_RTYPE_SERVERINTERPRETER_HPP
#define SERVER_RTYPE_SERVERINTERPRETER_HPP


#include <IInterpreter.hpp>
#include <functional>
#include <map>

class ServerInterpreter : public IInterpreter {
private:
    std::map<PacketType, std::function<void(const char *, uint32_t)> > packets;
public:
    ServerInterpreter();

    ~ServerInterpreter();

    void interpretButtonEvent(const char *data, uint32_t id);

    void interpretJoystickEvent(const char *data, uint32_t id);

    void interpretConnection(const char *data, uint32_t id);

    void interpretCreateGame(const char *data, uint32_t id);

    void interpretJoinGame(const char *data, uint32_t id);

    void interpretLaunchGame(const char *data, uint32_t id);

    void interpretPacket(const char *data, PacketType type, uint32_t);

    void interpretRequireGameList(const char *data, uint32_t);

    void interpretRequireRoomInfo(const char *data, uint32_t id);

    void interpretLeaveRoom(const char *data, uint32_t id);

    void interpretDisconnectGame(const char *data, uint32_t id);
};


#endif //SERVER_RTYPE_SERVERINTERPRETER_HPP
