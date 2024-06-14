/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Msz
*/

#include "Msz.hpp"

void gui::Msz::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    client.queueRequest("msz");
}

void gui::Msz::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;

    iss >> token >> x >> y;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    Vector2u mapSize(x, y);

    if (gameData.mapRef().mapSize() != Vector2u(0, 0))
        throw std::invalid_argument("Map size already set.");
    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    gameData.mapRef().setMapSize(mapSize);
    gameData.mapRef().initMapContent(mapSize);
}
