/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pbc
*/

#include "Pbc.hpp"

void gui::Pbc::stage(ntw::Client &client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pbc: can't be staged." << std::endl;
}

void gui::Pbc::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::string message;

    iss >> token >> playerId >> message;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    std::cout << "Player " << playerId << " broadcasted: " << message << std::endl;

    auto player = gameData.getPlayerById(playerId);
    if (player.has_value())
        std::cout << "Player broadcasted: " << message << std::endl;
        // player.value().setBroadcast(message);
}
