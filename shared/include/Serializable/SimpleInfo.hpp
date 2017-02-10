#ifndef 		CLIENT_INFO_PACKET_HPP_
# define 		CLIENT_INFO_PACKET_HPP_

# include "ASerializable.hpp"

struct SimpleInfo : public ASerializable
{
public:
	SimpleInfo();
	SimpleInfo(PacketType);
	~SimpleInfo();

    std::string           serialize() const;
    void            operator<<(const char*);
    ISerializable* 		clone() const;
};

std::ostream&       operator<<(std::ostream &os, const SimpleInfo&);

#endif