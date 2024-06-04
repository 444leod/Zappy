/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ZappyClient
*/

#pragma once

#include <cstdint>
#include <string>
#include <SFML/Network.hpp>
#include <chrono>
#include <optional>

namespace GUI {
    /**
     * @brief Class to handle the connection to the server
     * @details Class to handle the connection to the server
     */
    class ZappyClient {
        public:
            ZappyClient(uint16_t port) noexcept;
            ~ZappyClient() = default;

            void connectToServer();
            void queueRequest(const std::string& request);
            void queueRequests(const std::vector<std::string>& requests);
            void sendRequests(std::optional<std::chrono::milliseconds> timeout = std::nullopt);
            bool receive();
            void disconnect();
            const std::string& popResponse();
            bool hasResponses() const noexcept { return !_responses.empty(); }

            class ZappyClientException : public std::exception {
                public:
                    ZappyClientException(const std::string& message) : _message(message) {}
                    const char* what() const noexcept override { return _message.c_str(); }
                private:
                    std::string _message;
            };

        protected:
        private:
            uint16_t _port;
            sf::TcpSocket _socket;
            std::vector<std::string> _responses = {};
            std::vector<std::string> _requests = {};
            std::string _buffer;

            bool _connected;
    };
}

