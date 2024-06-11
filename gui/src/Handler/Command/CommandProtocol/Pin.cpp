/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pin
*/

#include "Pin.hpp"

void gui::Pin::stage(ntw::Client &client, std::string parameters)
{
    std::istringstream iss(parameters);
    std::uint32_t playerId;

    iss >> playerId;

    client.queueRequest("pin " + std::to_string(playerId));
}

void gui::Pin::receive(std::string command, GameData &gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t x, y;
    std::uint32_t food;
    std::uint32_t linemate, deraumere, sibur, mendiane, phiras, thystame;

    iss >> token >> playerId >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    Vector2u pos(x, y);
    Character player;
    Rocks rocks;

    rocks.linemate.setQuantity(linemate);
    rocks.deraumere.setQuantity(deraumere);
    rocks.sibur.setQuantity(sibur);
    rocks.mendiane.setQuantity(mendiane);
    rocks.phiras.setQuantity(phiras);
    rocks.thystame.setQuantity(thystame);

    gameData.players().at(playerId)->setFood(food);
    gameData.players().at(playerId)->setRocks(rocks);
}
