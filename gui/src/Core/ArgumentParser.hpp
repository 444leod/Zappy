/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ArgumentParser
*/

#pragma once

#include <string>
#include <cstdint>

namespace gui {

    /**
     * @brief Encapsulate the process of parsing arguments.
     * @warning Throws incorrect_argument exception when failing.
     */
    class ArgumentParser {
        public:
            /**
             * @brief Parses argument.
             * @warning Throws when failing.
             *
             * @param ac The argument count given to the main function
             * @param av The argument values given to the main function
             */
            ArgumentParser(int ac, char **av);
            ~ArgumentParser() = default;

            /**
             * @brief Gets the port (`-p`) argument value.
             */
            std::uint16_t port() const { return this->_port; }

            /**
             * @brief Gets the host (`-h`) argument value.
             * @note Default is `"localhost"`
             */
            const std::string& host() const { return this->_host; }
        protected:
        private:
            std::uint16_t _port = 0;
            std::string _host = "localhost";
    };
}
