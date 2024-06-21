/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Enw
*/

#include "Enw.hpp"

void gui::Enw::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)client;
    (void)parameters;
    std::cerr << "Command enw: can't be staged." << std::endl;
}

void gui::Enw::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::int32_t eggId, playerId;
    std::uint32_t x, y;

    iss >> token >> eggId >> playerId >> x >> y;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Invalid position");
    if (playerId == -1) {
        std::shared_ptr<gui::Egg> egg = std::make_shared<gui::Egg>(eggId, Vector2u(x, y), "");
        auto tile = gameData->map().at(Vector2u(x, y));
        tile->addEntity(egg);
        gameData->addEgg(egg);
        egg->setSkin("egg");
        std::srand(std::time(nullptr));
        egg->setRandomOffset(Vector2f(static_cast<float>(rand() % 30), (rand() % 30)));
        return;
    }
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");

    auto player = gameData->getPlayerById(playerId);
    if (player.has_value()) {
        std::shared_ptr<gui::Egg> egg = std::make_shared<gui::Egg>(eggId, Vector2u(x, y), player.value()->teamName());
        player.value()->layEgg(true);
        auto tile = gameData->map().at(Vector2u(x, y));
        tile->addEntity(egg);
        gameData->addEgg(egg);
        std::srand(std::time(nullptr));
        egg->setRandomOffset(Vector2f(static_cast<float>(rand() % 30), (rand() % 30)));
    }
}
