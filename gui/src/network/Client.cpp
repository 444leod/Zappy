/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Client
*/

#include "Client.hpp"
#include <SFML/System/Time.hpp>

gui::ntw::Client::Client(uint16_t port) noexcept : _port(port)
{
}

gui::ntw::Client::~Client()
{
    if (_connected)
        this->disconnect();
}

void gui::ntw::Client::connectToServer()
{
    sf::Socket::Status status = _socket.connect("localhost", _port, sf::seconds(5));
    auto now = std::chrono::system_clock::now();

    if (status != sf::Socket::Done)
        throw ClientException("Failed to connect to server (ip: localhost, port: " + std::to_string(_port) + ")");

    _socket.setBlocking(false);
    _connected = true;

    while (!this->receive() && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - now).count() < 5);

    if (!this->hasResponses())
        throw ClientTimeoutException("Failed to connect to server (welcome not received.)");

    std::string message = this->popResponse();
    if (message != "WELCOME")
        throw ClientException("Failed to connect to server (welcome not received.)");
    this->queueRequest("GRAPHIC");
    this->sendRequests();
}

void gui::ntw::Client::sendRequests(std::optional<std::chrono::milliseconds> timeout)
{
    if (!_connected)
        throw ClientNotConnectedException();
    if (_requests.empty())
        throw ClientException("No message to send");
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
                throw ClientTimeoutException("Failed to send message to server (timeout)");
            throw ClientException("Failed to send message to server");
        }
    }
}

void gui::ntw::Client::queueRequest(const std::string& request)
{
    if (request.empty())
        throw ClientException("Empty message");

    std::string requestCopy = (request.back() == '\n') ? request : request + '\n';
    _requests.push_back(requestCopy);
}

void gui::ntw::Client::queueRequests(const std::vector<std::string>& requests)
{
    for (const std::string& request : requests) {
        this->queueRequest(request);
    }
}

bool gui::ntw::Client::receive()
{
    if (!_connected)
        throw ClientNotConnectedException();

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

void gui::ntw::Client::disconnect()
{
    if (!_connected)
        throw ClientNotConnectedException();

    _socket.disconnect();
    _connected = false;
}

const std::string& gui::ntw::Client::popResponse()
{
    if (_responses.empty())
        throw ClientException("No message to pop");
    std::string& message = _responses.front();

    _responses.erase(_responses.begin());
    return message;
}