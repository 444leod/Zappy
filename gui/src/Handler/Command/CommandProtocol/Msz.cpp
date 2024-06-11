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
    client.queueRequest("msz\n");
}

void gui::Msz::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t width, height;

    iss >> token >> width >> height;
    Vector2u mapSize(width, height);

    gameData.mapRef().setMapSize(mapSize);
}
