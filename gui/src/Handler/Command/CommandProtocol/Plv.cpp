/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Plv
*/

#include "Handler/Command/CommandProtocol/Plv.hpp"

void gui::Plv::send(std::string command, ntw::Client &client)
{
    client.queueRequest(command + "\n");
    client.sendRequests();
}

void gui::Plv::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t level;

    iss >> token >> playerId >> level;
    // gameData.players().at(playerId)->increasePlayerLevel();
}
