/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#include "Ppo.hpp"

void gui::Ppo::stage(ntw::Client &client, std::string parameters)
{
    if (parameters.empty())
        throw std::invalid_argument("Invalid ppo arguments");

    client.queueRequest("ppo " + parameters);
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
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist in the game data.");

    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Player position is out of bounds.");
    gameData.players().at(playerId)->setPosition(Vector2u(x, y));

    auto it = _orientationMap.find(orientation);
    if (it != _orientationMap.end())
        playerOrientation = it->second;
    else
        throw std::invalid_argument("Invalid orientation: " + orientation);

    auto player = gameData.getPlayerById(playerId);
    if (player.has_value())
        player.value()->setOrientation(playerOrientation);
}
