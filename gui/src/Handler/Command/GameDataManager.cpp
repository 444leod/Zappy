/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GameDataManager
*/

#include "Handler/Command/GameDataManager.hpp"

void gui::GameDataManager::handleRequests()
{
    _client.queueRequests(_requests);
    _client.sendRequests(std::chrono::milliseconds(1000));
    _client.receive();

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
}
