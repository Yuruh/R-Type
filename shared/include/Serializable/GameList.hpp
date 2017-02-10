//
// Created by yuruh on 26/12/16.
//

#ifndef SHARED_GAMELIST_HPP
#define SHARED_GAMELIST_HPP


#include <Serializable/ASerializable.hpp>
#include <vector>

//todo : refacto en idList
struct GameList : public ASerializable
{
public:
    GameList();
    GameList(PacketType);
    ~GameList();


    std::string     serialize() const;
    void            operator<<(const char*);
    ISerializable* 		clone() const;

    std::vector<uint32_t>   gameIDs;
};

std::ostream&       operator<<(std::ostream &os, const GameList&);


#endif //SHARED_GAMELIST_HPP
