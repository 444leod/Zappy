/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pie
*/

#include "Pie.hpp"

void gui::Pie::stage(ntw::Client &client, std::string command)
{
    (void)command;
    (void)client;
}

void gui::Pie::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t result;

    iss >> token >> x >> y >> result;
    // gameData.setIncantationResult(Vetcor2u(x, y), result);
}
