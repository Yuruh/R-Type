//
// ClientInterpreter.hpp for  in /home/yuruh/rendu/cpp/rtype/shared/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Dec 13 12:52:14 2016 Antoine Lempereur
// Last update Thu Dec 15 16:13:45 2016 Antoine Lempereur
//

#ifndef INTERPRET_HPP_
#define INTERPRET_HPP_

#include "EntityPos.hpp"
#include "GameInfo.hpp"

#include <map>
#include <functional>
#include <memory>
#include <IInterpreter.hpp>

class ClientInterpreter : public IInterpreter
{
private:
    std::map<PacketType, std::function<void(const char*)> >  packets;
    void interpretEntityPos(const char*);
    void interpretConnection(const char *data);
    void interpretGameList(const char *);
    void interpretRoomInfo(const char *);
    void interpretGameJoined(const char *data);
    void interpretGameLaunched(const char *data);
    void interpretGameResult(const char *data);

public:
    ClientInterpreter ();
    ~ClientInterpreter ();
    void interpretPacket(const char *, PacketType, uint32_t);

};

#endif /* end of include guard: INTERPRET_HPP_ */
