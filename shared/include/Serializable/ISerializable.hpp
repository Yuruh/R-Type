#ifndef 	IPACKET_HPP_
# define 	IPACKET_HPP_

# include 		<iostream>
# include 		<cstdlib>
# include 		<stdio.h>
# include 		<string.h>

enum PacketType
{
	ENTITY_POS,
    DEATH_ENTITY,

	CONNECT,

    REQUIRE_GAME_LIST,
	GAME_LIST,

	REQUIRE_ROOM_INFO,
	ROOM_INFO,

	CREATE_GAME,

	JOIN_GAME,
	GAME_JOINED,

    LEAVE_ROOM,

	LAUNCH_GAME,
    GAME_LAUNCHED,

    GAME_WON,
    GAME_LOST,

    DISCONNECT_GAME,
	GAME_DISCONNECTED,

	DISCONNECT_CLIENT,
	CLIENT_DISCONNECTED,

	EVENT_BUTTON,
	EVENT_JOYSTICK,

	UNDEFINED
	// UNDEFINED is used as the maximum value of PacketType, keep it at the end
};

class  		ISerializable
{
public:
	ISerializable(){};
	virtual ~ISerializable(){};

	virtual std::string serialize() const = 0;
	virtual void 			operator<<(const char*) = 0;
	virtual ISerializable* 		clone() const = 0;
	virtual PacketType 		getType() const = 0;
};

#endif
