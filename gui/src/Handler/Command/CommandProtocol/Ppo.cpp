/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#include "Ppo.hpp"

void gui::Ppo::stage(ntw::Client &client, std::string parameters)
{
    client.queueRequest(parameters + "\n");
    client.sendRequests();
}

void gui::Ppo::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t x, y;
    std::string orientation;
    Orientation playerOrientation;

    iss >> token >> playerId >> x >> y >> orientation;

    auto it = _orientationMap.find(orientation);
    if (it != _orientationMap.end())
        playerOrientation = it->second;
    else
        throw std::invalid_argument("Invalid orientation: " + orientation);

    gameData.players().at(playerId)->setPosition(Vector2u(x, y));
    gameData.players().at(playerId)->setOrientation(playerOrientation);
}
