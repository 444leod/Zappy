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
    std::string msg;

    iss >> token >> playerId >> msg;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    std::cout << "Player " << playerId << " broadcasted: " << msg << std::endl;

    auto player = gameData.getPlayerById(playerId);
    if (player.has_value()) {
        message_t message = {
            .senderId = playerId,
            .message = msg,
            .teamName = player.value()->teamName(),
            .time = std::chrono::system_clock::now()
        };
        std::cout << "Player broadcasted: " << msg << std::endl;
        gameData.addMessage(message);
        player.value()->broadcast(message);
    }
}
