/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pic
*/

#include "Pic.hpp"

void gui::Pic::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
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
