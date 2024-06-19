/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgumentParser
*/

#pragma once

#include <map>
#include <vector>
#include <string>

namespace gui {
    class ArgumentParser {
        public:
            static std::map<std::string, std::vector<std::string>> parseArgs(int ac, char **av);
        protected:
        private:
    };
}
