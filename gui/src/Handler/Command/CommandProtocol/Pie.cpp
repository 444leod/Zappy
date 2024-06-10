/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pie
*/

#include "Handler/Command/CommandProtocol/Pie.hpp"

void gui::Pie::send(std::string command, ntw::Client &client)
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
