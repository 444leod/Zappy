/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pex
*/

#include "Pex.hpp"
#include "Expulse.hpp"
#include "Expulsed.hpp"

void gui::Pex::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pex: can't be staged." << std::endl;
}

void gui::Pex::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;

    iss >> token >> playerId;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist");
    auto player = gameData->getPlayerById(playerId);
    if (player.has_value()) {
        player.value()->expulse(true);
        player.value()->pushAnimation(std::make_shared<gui::animations::Expulse>(player.value()->skin(), player.value()));
        Vector2i pos = Vector2i(player.value()->position().x(), player.value()->position().y());
        switch (player.value()->orientation()) {
            case gui::Orientation::SOUTH:
                pos += Vector2i(0, -1);
                break;
            case gui::Orientation::NORTH:
                pos += Vector2i(0, 1);
                break;
            case gui::Orientation::EAST:
                pos += Vector2i(-1, 0);
                break;
            case gui::Orientation::WEST:
                pos += Vector2i(1, 0);
                break;
        }
        auto entities = gameData->map().at(pos)->entities();
        for (auto &entity : entities) {
            if (entity->type() == gui::AEntity::EntityType::PLAYER) {
                entity->pushAnimation(std::make_shared<gui::animations::Expulsed>(entity->skin(), std::dynamic_pointer_cast<gui::Player>(entity)));
            } else {
                gameData->removeEgg(entity->id());
            }
        }
    }
}
