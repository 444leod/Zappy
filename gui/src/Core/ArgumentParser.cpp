/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgumentParser
*/

#include "ArgumentParser.hpp"

std::map<std::string, std::vector<std::string>> gui::ArgumentParser::parseArgs(int ac, char **av)
{
    std::vector<std::string> args(av + 1, av + ac);
    std::map<std::string, std::vector<std::string>> flags;
    std::string currentFlag;

    for (auto it = args.begin(); it != args.end(); ++it) {
        if (it->front() == '-') {
            currentFlag = it->substr(1);
            flags[currentFlag] = {};
        } else {
            flags[currentFlag].push_back(*it);
        }
    }
    return flags;
}
