/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Client
*/

#pragma once

#include <cstdint>
#include <string>
#include <SFML/Network.hpp>
#include <chrono>
#include <optional>

namespace gui {
    namespace ntw {
         /**
         * @brief Class to handle the connection to the server
         * @details Class to handle the connection to the server
         */
        class Client {
            public:
                /**
                 * @brief Construct a new Client::Client object
                 * @details Construct a new Client::Client object
                 *
                 * @param port The port to connect to
                 * @param teamName The team name
                */
                Client(uint16_t port) noexcept;
                /**
                 * @brief Destroy the Client::Client object and disconnect from the server
                 * @details Destroy the Client::Client object and disconnect from the server
                */
                ~Client();

                /**
                 * @brief Connects the socket to the server
                 * @details Connects the socket to the server, receives the welcome message and sends the team name
                 *
                 * @throw ClientException if the connection to the server fails
                 * @throw ClientException if the welcome message is not received
                 * @throw ClientException if the message could not be sent
                 * @throw ClientTimeoutException if the message could not be sent within the timeout
                */
                void connectToServer();

                /**
                 * @brief Sends the queued requests to the server
                 * @details Sends the queued requests to the server
                 *
                 * @param timeout The timeout for the send operation, if not specified, the operation will block until the message is sent
                 *
                 * @throw ClientNotConnectedException if the socket is not connected
                 * @throw ClientException if there is no message to send
                 * @throw ClientException if the message could not be sent
                 * @throw ClientTimeoutException if the message could not be sent within the timeout
                */
                void queueRequest(const std::string& request);

                /**
                 * @brief Queues a request
                 * @details Queues a request
                 *
                 * @param request The request to queue
                 *
                 * @throw ClientException if the request is empty
                */
                void queueRequests(const std::vector<std::string>& requests);

                /**
                 * @brief Queues multiple requests
                 * @details Queues multiple requests
                 *
                 * @param requests The requests to queue
                 *
                 * @throw ClientException if a request is empty
                */
                void sendRequests(std::optional<std::chrono::milliseconds> timeout = std::nullopt);

                /**
                 * @brief Receives messages from the server
                 * @details Receives messages from the server and stores them in the message queue
                 *
                 * @return bool true if a message has been received, false otherwise
                 *
                 * @throw ClientNotConnectedException if the socket is not connected
                */
                bool receive();

                /**
                 * @brief Disconnects the socket from the server
                 *
                 * @throw ClientNotConnectedException if the socket is not connected
                */
                void disconnect();

                /**
                 * @brief Pops the first message from the message queue
                 * @details If the queue is empty, throws a ClientException
                 *        with the message "No message to pop"
                 *  else, pops the first message from the queue and returns it
                 *
                 * @return const std::string&
                 *
                 * @throw ClientException if the queue is empty
                */
                const std::string& popResponse();

                /**
                 * @brief Checks if there are messages in the message queue
                 * @details Checks if there are messages in the message queue
                 *
                 * @return bool true if there are messages in the queue, false otherwise
                */
                bool hasResponses() const noexcept { return !_responses.empty(); }

                /**
                 * @brief Exception class for the Client (Global scope)
                 * @details Exception class for the Client (Global scope)
                */
                class ClientException : public std::exception {
                    public:
                        ClientException(const std::string& message) : _message(message) {}
                        const char* what() const noexcept override { return _message.c_str(); }
                    private:
                        std::string _message;
                };

                /**
                 * @brief Exception class for the Client when the client is not connected
                 * @details Exception class for the Client when the client is not connected
                */
                class ClientNotConnectedException : public ClientException {
                    public:
                        ClientNotConnectedException() : ClientException("The client is not connected to the server.") {}
                };

                /**
                 * @brief Exception class for the Client when the client times out
                 * @details Exception class for the Client when the client times out
                */
                class ClientTimeoutException : public ClientException {
                    public:
                        ClientTimeoutException(const std::string& message) : ClientException(message) {}
                };

            protected:
            private:
                uint16_t _port;
                sf::TcpSocket _socket;
                std::vector<std::string> _responses = {};
                std::vector<std::string> _requests = {};
                std::string _buffer;

                bool _connected = false;
        };
    }
}
