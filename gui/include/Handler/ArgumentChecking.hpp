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
#include <algorithm>

namespace gui {
    class ArgumentChecking {
        public:
            /**
             * @brief Check the flags of the arguments
             * @param args The arguments
             * @return The flags in a map
            */
            std::map<std::string, std::string> checkFlags(std::vector<std::string> args) const;

            /**
             * @brief Print the usage
            */
            void printUsage() const;

            /**
             * @brief Check the arguments
             * @param ac The number of arguments
             * @param av The arguments
            */
            void checkArgs(int ac, char **av) const;
    };
}
