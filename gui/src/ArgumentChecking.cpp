/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ArgumentChecking
*/

#include "ArgumentChecking.hpp"

/**
 * @brief Print the usage
 */
void gui::ArgumentChecking::printUsage() const
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
std::map<std::string, std::string> gui::ArgumentChecking::checkFlags(std::vector<std::string> args) const
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
void gui::ArgumentChecking::checkArgs(int ac, char **av) const
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
