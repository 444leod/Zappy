/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "Handler/Command/GameDataManager.hpp"
#include <cstring>

void printUsage()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "port: the port number" << std::endl;
    std::cout << "machine: hostname of the server" << std::endl;
}

void checkArgs(int ac, char **av)
{
    if (std::strcmp(av[1], "-help") == 0) {
        printUsage();
        return;
    }
    if (ac != 5) {
        printUsage();
        throw std::invalid_argument("Invalid number of arguments");
    }
    if (std::strcmp(av[1], "-p") == 0) {
        if (std::atoi(av[2]) < 1024 || std::atoi(av[2]) > 65535)
            throw std::invalid_argument("Port must be between 1024 and 65535");
        if (std::strcmp(av[3], "-h") == 0) {
            if (std::strlen(av[4]) < 1)
                throw std::invalid_argument("Invalid hostname");
        }
    } else
        throw std::invalid_argument("Invalid arguments, try using -help for more information");
}

int main(int ac, char **av)
{
    try {
        checkArgs(ac, av);
        std::uint32_t port = std::atoi(av[2]);
        gui::GameDataManager gameDataManager(port);
        while (1)
            gameDataManager.handleRequests();
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientTimeoutException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientNotConnectedException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const gui::ntw::Client::ClientException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
