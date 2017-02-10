#ifndef 		GAME_INFO_PACKET_HPP_
# define 		GAME_INFO_PACKET_HPP_

# include "ASerializable.hpp"

class GameInfo : public ASerializable
{
public:
	GameInfo();
	GameInfo(PacketType);
	~GameInfo();
	
	uint32_t 		getPlayerId() const;
	void 			setPlayerId(uint32_t);
	uint32_t 		getGameId() const;
	void 			setGameId(uint32_t);

    std::string     serialize() const;
    void            operator<<(const char*);
    ISerializable* 		clone() const;


private:	
	uint32_t 		_playerId;
	uint32_t 		_gameId;
};

std::ostream&       operator<<(std::ostream &os, const GameInfo&);

#endif