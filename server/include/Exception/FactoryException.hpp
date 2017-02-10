//
// Created by wasta-geek on 10/12/16.
//

#ifndef SERVER_RTYPE_FactoryEXCEPTION_HPP
#define SERVER_RTYPE_FactoryEXCEPTION_HPP

class FactoryException : public std::exception
{
public:

    FactoryException(const char* message):
            _message(message)
    {
    }

    FactoryException(const std::string& message):
            _message(message)
    {
    }

    virtual ~FactoryException(){}

   const char* what() const throw() {
        return _message.c_str();
    }

protected:
    std::string _message;
};

#endif //SERVER_RTYPE_FactoryEXCEPTION_HPP
