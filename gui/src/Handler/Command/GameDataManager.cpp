/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameDataManager
*/

#include "Handler/Command/GameDataManager.hpp"

void gui::GameDataManager::handleRequests()
{
    // fd_set readFds;
    // struct timeval timeout = {0, 0};
    // FD_ZERO(&readFds);
    // FD_SET(0, &readFds);
    // if (select(1, &readFds, NULL, NULL, &timeout) > 0) {
    //     std::string input;
    //     std::getline(std::cin, input);
    //     std::printf("\033[A\33[2K\r -> %s\n", input.c_str());
    //     if (std::cin.eof())
    //         throw std::exception();
    //     _client.queueRequest(input);
    // }

    try {
        _client.receive();
        if (_client.hasRequests())
            _client.sendRequests(std::chrono::milliseconds(1));
        while (_client.hasResponses()) {
            std::string response = _client.popResponse();
            std::istringstream iss(response);
            std::string token;
            iss >> token;

            auto it = _responseHandlers.find(token);
            if (it != _responseHandlers.end()) {
                it->second->receive(response, _gameData);
            }
        }
    } catch (const ntw::Client::ClientTimeoutException& e) {
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

}
