/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Enw
*/

#include "Enw.hpp"

void gui::Enw::stage(ntw::Client &client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command enw: can't be staged." << std::endl;
}

void gui::Enw::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t eggId, playerId;
    std::uint32_t x, y;

    iss >> token >> eggId >> playerId >> x >> y;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData.eggExists(eggId))
        throw std::invalid_argument("Egg does not exist");
    if (!gameData.playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Invalid position");

    auto player = gameData.getPlayerById(playerId);
    if (player.has_value()) {
        std::cout << "Player " << playerId << " laid an egg with id " << eggId << std::endl;
        std::shared_ptr<gui::Egg> egg = std::make_shared<gui::Egg>(eggId, Vector2u(x, y), player.value()->teamName());
        player.value()->isLayingAnEgg(false);
    }
}
