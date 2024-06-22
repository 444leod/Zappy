/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgumentParser
*/

#pragma once

#include <string>

namespace gui {
    class ArgumentParser {
        public:
            ArgumentParser(int ac, char **av);
            ~ArgumentParser() = default;

            std::uint16_t port() const { return this->_port; }
            const std::string& host() const { return this->_host; }
        protected:
        private:
            std::uint16_t _port = 0;
            std::string _host = "localhost";
    };
}
