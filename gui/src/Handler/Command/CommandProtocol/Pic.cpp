/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#include "Handler/Command/CommandProtocol/Pic.hpp"

void gui::Pic::send(std::string command, ntw::Client &client)
{
    (void)command;
    (void)client;
}

void gui::Pic::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t level;
    std::uint32_t playerId;

    iss >> token >> x >> y >> level;
    while (iss >> playerId) {
        // gameData.players().at(playerId).setIsIncantating(true);
    }
}
