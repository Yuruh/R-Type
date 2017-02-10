#ifndef 		APACKET_HPP_
# define 		APACKET_HPP_

# include "ISerializable.hpp"

class 			ASerializable : public ISerializable
{
public:
	ASerializable();
	virtual ~ASerializable(){};

	virtual std::string		serialize() const = 0;
	virtual void 			operator<<(const char*) = 0;
	virtual ISerializable* 		clone() const = 0;

	PacketType 				getType() const;

	uint32_t        errorCode;


protected:
	PacketType 		_type;

    template <typename T>
    T               parseType(const char *bytes, unsigned int it)
    {
        char*   		byteValue = new char[sizeof(T)];
        T	            value;

        memcpy(byteValue, &bytes[it], sizeof(T));
        memcpy(&value, byteValue, sizeof(T));
        delete[] byteValue;
        return (value);
    }
};

#endif
