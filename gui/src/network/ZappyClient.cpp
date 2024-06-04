/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ZappyClient
*/

#include "ZappyClient.hpp"
#include <SFML/System/Time.hpp>

/**
 * @brief Construct a new ZappyClient::ZappyClient object
 * @details Construct a new ZappyClient::ZappyClient object
 *
 * @param port The port to connect to
 * @param teamName The team name
*/
GUI::ZappyClient::ZappyClient(uint16_t port) noexcept : _port(port)
{
}

/**
 * @brief Connects the socket to the server
 * @details Connects the socket to the server, receives the welcome message and sends the team name
 *
 * @throw ZappyClientException if the connection to the server fails
 * @throw ZappyClientException if the welcome message is not received
 * @throw ZappyClientException if the message could not be sent
 * @throw ZappyClientException if the message could not be sent within the timeout
*/
void GUI::ZappyClient::connectToServer()
{
    sf::Socket::Status status = _socket.connect("localhost", _port, sf::seconds(5));
    auto now = std::chrono::system_clock::now();

    if (status != sf::Socket::Done)
        throw ZappyClientException("Failed to connect to server (ip: localhost, port: " + std::to_string(_port) + ")");

    _socket.setBlocking(false);
    _connected = true;

    while (!this->receive() && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - now).count() < 5);

    if (!this->hasResponses())
        throw ZappyClientException("Failed to connect to server (welcome not received.)");

    std::string message = this->popResponse();
    if (message != "WELCOME")
        throw ZappyClientException("Failed to connect to server (welcome not received.)");
    this->queueRequest("GRAPHIC");
    this->sendRequests();
}

/**
 * @brief Sends the queued requests to the server
 * @details Sends the queued requests to the server
 *
 * @param timeout The timeout for the send operation, if not specified, the operation will block until the message is sent
 *
 * @throw ZappyClientException if the socket is not connected
 * @throw ZappyClientException if there is no message to send
 * @throw ZappyClientException if the message could not be sent
 * @throw ZappyClientException if the message could not be sent within the timeout
*/
void GUI::ZappyClient::sendRequests(std::optional<std::chrono::milliseconds> timeout)
{
    if (!_connected)
        throw ZappyClientException("Not connected to server");
    if (_requests.empty())
        throw ZappyClientException("No message to send");
    std::string fullRequest;

    for (const std::string& request : _requests)
        fullRequest += request;

    std::size_t totalSent = 0;
    std::size_t messageLength = fullRequest.size();
    sf::Socket::Status status;
    auto now = std::chrono::system_clock::now();
    std::chrono::milliseconds duration;

    while (totalSent < messageLength) {
        std::size_t sent;
        status = _socket.send(fullRequest.c_str() + totalSent, messageLength - totalSent, sent);
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now);
        if (status == sf::Socket::Done) {
            totalSent += sent;
        } else if (status == sf::Socket::NotReady && timeout.has_value() && duration < timeout.value()) {
            sf::sleep(sf::milliseconds(10));
        } else {
            if (status == sf::Socket::NotReady)
                throw ZappyClientException("Failed to send message to server (timeout)");
            throw ZappyClientException("Failed to send message to server");
        }
    }
}

/**
 * @brief Queues a request
 * @details Queues a request
 *
 * @param request The request to queue
 *
 * @throw ZappyClientException if the request is empty
*/
void GUI::ZappyClient::queueRequest(const std::string& request)
{
    if (request.empty())
        throw ZappyClientException("Empty message");

    std::string requestCopy = (request.back() == '\n') ? request : request + '\n';
    _requests.push_back(requestCopy);
}

/**
 * @brief Queues multiple requests
 * @details Queues multiple requests
 *
 * @param requests The requests to queue
 *
 * @throw ZappyClientException if a request is empty
*/
void GUI::ZappyClient::queueRequests(const std::vector<std::string>& requests)
{
    for (const std::string& request : requests) {
        this->queueRequest(request);
    }
}

/**
 * @brief Receives messages from the server
 * @details Receives messages from the server and stores them in the message queue
 *
 * @return bool true if a message has been received, false otherwise
 *
 * @throw ZappyClientException if the socket is not connected
*/
bool GUI::ZappyClient::receive()
{
    if (!_connected)
        throw ZappyClientException("Not connected to server");

    char buffer[1024];
    std::size_t received;
    bool hasReceived = false;

    while (_socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
        _buffer.append(buffer, received);
        std::size_t pos = _buffer.find('\n');
        while (pos != std::string::npos) {
            _responses.push_back(_buffer.substr(0, pos));
            _buffer.erase(0, pos + 1);
            pos = _buffer.find('\n');
        }
        hasReceived = true;
    }
    return hasReceived;
}

/**
 * @brief Disconnects the socket from the server
 *
 * @throw ZappyClientException if the socket is not connected
*/
void GUI::ZappyClient::disconnect()
{
    if (!_connected)
        throw ZappyClientException("Not connected to server");

    _socket.disconnect();
}

/**
 * @brief Pops the first message from the message queue
 * @details If the queue is empty, throws a ZappyClientException
 *        with the message "No message to pop"
 *  else, pops the first message from the queue and returns it
 *
 * @return const std::string&
 *
 * @throw ZappyClientException if the queue is empty
*/
const std::string& GUI::ZappyClient::popResponse()
{
    if (_responses.empty())
        throw ZappyClientException("No message to pop");
    std::string& message = _responses.front();

    _responses.erase(_responses.begin());
    return message;
}
