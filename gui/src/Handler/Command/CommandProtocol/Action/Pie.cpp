/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pie
*/

#include "Pie.hpp"

void gui::Pie::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pie: can't be staged" << std::endl;
}

void gui::Pie::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t result;

    iss >> token >> x >> y >> result;

    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    if (result != 1 || result != 0)
        throw std::invalid_argument("Invalid incantation result.");
    // gameData.setIncantationResult(Vetcor2u(x, y), result);
}
