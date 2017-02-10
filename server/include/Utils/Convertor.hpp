//
// Created by ossalag on 13/12/16.
//

#ifndef SERVER_RTYPE_CONVERTOR_HPP
#define SERVER_RTYPE_CONVERTOR_HPP

#define     RES_CLIENT(a)   a - (a * PERCENT(ZOOM))

#define     PERCENT(a)      a / 100

#define     ZOOM            40

#define     SPAWN_ZONE      300

class Convertor
{
    Convertor();
    ~Convertor();

public:
    static float toPercentClient(float const i, char const flag);

    static float toPercentServer(float const i, char const flag);

    static float toRelativeClient(float const i, char const flag);

    static float toRelativeServer(float const i, char const flag);

    static void normalizeVector(float &x, float &y);
};

#endif //SERVER_RTYPE_CONVERTOR_HPP
