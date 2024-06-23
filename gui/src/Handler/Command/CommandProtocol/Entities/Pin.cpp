/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pin
*/

#include "Pin.hpp"

void gui::Pin::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    if (parameters.empty())
        throw std::invalid_argument("Invalid pin arguments");

    client->queueRequest("pin " + parameters);
}

void gui::Pin::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t linemate, deraumere, sibur, mendiane, phiras, thystame, food;

    iss >> token >> playerId >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist in the game data.");

    Rocks rocks;

    rocks.linemate.setQuantity(linemate);
    rocks.deraumere.setQuantity(deraumere);
    rocks.sibur.setQuantity(sibur);
    rocks.mendiane.setQuantity(mendiane);
    rocks.phiras.setQuantity(phiras);
    rocks.thystame.setQuantity(thystame);


    auto players = gameData->getPlayerById(playerId);
    if (players.has_value()) {
        players.value()->setFood(food);
        players.value()->setRocks(rocks);
    }
}
