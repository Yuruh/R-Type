//
// Created by yuruh on 30/11/16.
//

#ifndef RTYPE_IWINDOW_HPP
#define RTYPE_IWINDOW_HPP


class IWindow
{
public:
    virtual void handleEvents(bool *)= 0;
    virtual void quit()= 0;
};


#endif //RTYPE_IWINDOW_HPP
