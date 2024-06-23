/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pie
*/

#include "Pie.hpp"

void gui::Pie::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pie: can't be staged." << std::endl;
}

void gui::Pie::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    (void)gameData;
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t result;

    iss >> token >> x >> y >> result;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    if (result != 1 && result != 0)
        throw std::invalid_argument("Invalid incantation result.");
    if (result == 0)
        return;
    auto entities = gameData->map().at(Vector2u{x, y})->entities();
    for (auto &entity : entities) {
        if (entity->type() == gui::AEntity::EntityType::PLAYER) {
            auto player = std::dynamic_pointer_cast<Player>(entity);
            player->increaseLevel();
        }
    }

}
