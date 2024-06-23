/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgumentParser
*/

#include "ArgumentParser.hpp"
#include <iostream>
#include <map>
#include <regex>

gui::ArgumentParser::ArgumentParser(int ac, char **av)
{
    std::uint32_t keys = 0;
    std::map<std::string, std::string> params;
    std::string key = "";

    for (int i = 0; i < ac; i++) {
        std::string arg = av[i];
        if (arg.starts_with('-')) {
            key = arg;
            params[key] = "";
            keys++;
        } else {
            params[key] = arg;
        }
    }

    if (!params.contains("-p"))
        throw std::invalid_argument("Port number (-p) is missing.");
    if (params.at("-p").size() == 0)
        throw std::invalid_argument("Invalid port number (-p).");
    auto port = std::atol(params.at("-p").c_str());
    if (port < 0 || port > 65535)
        throw std::invalid_argument("Invalid port number (-p).");
    this->_port = port;
    keys--;

    if (params.contains("-h")) {
        if (params.at("-h").size() == 0) {
            std::cerr << "[ERROR] Invalid host address (-h)." << std::endl;
            std::cerr << "\tFalling back to 'localhost'." << std::endl;
        } else {
            std::string copy = params.at("-h");
            auto exp = std::regex("([0-9]{1,}.){3}[0-9]{1,}");
            if(!std::regex_match(copy, exp)) {
                std::cerr << "[ERROR] Invalid host address (-h)." << std::endl;
                std::cerr << "\tFalling back to 'localhost'." << std::endl;
            } else
                this->_host = params.at("-h");
        }
        keys--;
    }

    if (keys > 0)
        throw std::invalid_argument("Too many or unknown arguments.");
}
