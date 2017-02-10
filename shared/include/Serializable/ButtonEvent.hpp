#ifndef 		EVENT_PACKET_HPP_
# define 		EVENT_PACKET_HPP_

# include "ASerializable.hpp"

enum ButtonType
{
	UNKNOWN_BUTTON,
	ESCAPE,
	SPACE,
	RETURN,
	BACKSPACE,
	Z, UP,
	Q, DOWN,
	S, LEFT,
	D, RIGHT,
};


class  			ButtonEvent : public ASerializable
{
public:
	ButtonEvent();
	ButtonEvent(PacketType);
	~ButtonEvent();

	void        setButtonType(ButtonType);
	ButtonType  getButtonType(void) const;

	std::string           serialize() const;
	void            operator<<(const char*);
	ISerializable* 		clone() const;

private:
	ButtonType  _buttonType;
};

std::ostream&       operator<<(std::ostream &os, const ButtonEvent&);

#endif