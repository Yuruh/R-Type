//
// main.cpp for  in /home/wasta-geek/rendu/TEK3/ADVANCED_CPP/rtype/server
//
// Made by Wasta-Geek
// Login   <corentin.ducatez@epitech.eu@epitech.net>
//
// Started on  Wed Dec  7 16:05:09 2016 Wasta-Geek
// Last update Sat Dec 17 20:36:56 2016 Raphael Thiebault
//

#include <Core.hpp>
#include <sstream>

int	main(int argc, char **argv)
{
    uint16_t    port = 4242;

    if (argc > 1) {
        std::string         str(argv[1]);
        std::stringstream   ss_port(str);

        ss_port >> port;
    }
    try {
        Core::getInstance().run(port);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}
