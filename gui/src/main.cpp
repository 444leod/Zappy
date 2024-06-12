/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include "GameDataManager.hpp"
#include "ArgumentChecking.hpp"
#include <cstring>

/**
 * @brief Print the usage
 */
void gui::ArgumentChecking::printUsage()
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "port: the port number" << std::endl;
    std::cout << "machine: hostname of the server" << std::endl;
}

/**
 * @brief Check the flags
 * @param args The arguments
 * @return The flags in a map
 */
std::map<std::string, std::string> gui::ArgumentChecking::checkFlags(std::vector<std::string> args)
{
    int p_count = std::count(args.begin(), args.end(), "-p");
    int h_count = std::count(args.begin(), args.end(), "-h");
    std::map<std::string, std::string> flags;

    if (p_count != 1 || h_count != 1)
        throw std::invalid_argument("You only need one -p and one -h flag.");
    for (auto it = args.begin(); it != args.end(); ++it) {
        if (it->front() == '-') {
            if (std::next(it) != args.end()) {
                flags[it->substr(1)] = *std::next(it);
            }
        }
    }
    return flags;
}

/**
 * @brief Check the arguments
 * @param ac The number of arguments
 * @param av The arguments
 */
void gui::ArgumentChecking::checkArgs(int ac, char **av)
{
    std::vector<std::string> args(av, av + ac);
    std::map<std::string, std::string> flags;

    if (ac != 5) {
        printUsage();
        throw std::invalid_argument("Invalid number of arguments");
    }
    flags = checkFlags(args);
    if (flags.find("p") != flags.end()) {
        std::string port = flags["p"];
        if (port.find_first_not_of("0123456789") != std::string::npos)
            throw std::invalid_argument("Port must be a number");
        if (std::stoi(port) < 1024 || std::stoi(port) > 65535)
            throw std::invalid_argument("Port must be between 1024 and 65535");
    }
    if (flags.find("h") != flags.end()) {
        std::string hostname = flags["h"];
        if (hostname.empty())
            throw std::invalid_argument("Hostname must not be empty");
    }
}

int main(int ac, char **av)
{
    try {
        std::shared_ptr<gui::ArgumentChecking> argCheck = std::make_shared<gui::ArgumentChecking>();
        argCheck->checkArgs(ac, av);
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
