/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ArgumentChecking
*/

#pragma once

#include <iostream>
#include <map>
#include <vector>

namespace gui {
    class ArgumentChecking {
        public:
            std::map<std::string, std::string> checkFlags(std::vector<std::string> args);
            void printUsage();
            void checkArgs(int ac, char **av);
    };
}
