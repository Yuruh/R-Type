#include "Core.hpp"
#include <sstream>


int main(int argc, char **argv)
{
    std::string     hostname = "127.0.0.1";
    uint16_t        port     = 4242;

    if (argc > 1) {
        hostname = argv[1];
    }
    if (argc > 2) {
        std::string         str(argv[2]);
        std::stringstream   ss_port(str);

        ss_port >> port;
    }
    try {
        Core::getInstance().run(hostname, port);
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}
