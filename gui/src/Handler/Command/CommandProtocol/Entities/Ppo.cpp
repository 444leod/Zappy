/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Ppo
*/

#include "Ppo.hpp"
#include "Walk.hpp"

void gui::Ppo::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    if (parameters.empty())
        throw std::invalid_argument("Invalid ppo arguments");

    client->queueRequest("ppo " + parameters);
}

void gui::Ppo::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId;
    std::uint32_t x, y;
    std::string orientation;
    Orientation playerOrientation;

    iss >> token >> playerId >> x >> y >> orientation;
    std::cout << "Ppo command received: " << playerId << " " << x << " " << y << " " << orientation << std::endl;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");

    if (!gameData->playerExists(playerId))
        throw std::invalid_argument("Player does not exist in the game data.");

    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Player position is out of bounds.");

    auto player = gameData->getPlayerById(playerId);
    if (!player.has_value())
        throw std::invalid_argument("Player does not exist in the game data.");
    if (player.value()->position() != Vector2u(x, y)) {
        std::cout << "Player position changed from: " << player.value()->position().x() << ", " << player.value()->position().y() << " to: " << x << ", " << y << std::endl;
        player.value()->setPosition(Vector2u(x, y));
        player.value()->setTileDisplayOffset(gameData->map().at(Vector2u(x, y))->offset());
        player.value()->pushAnimation(std::make_shared<gui::animations::Walk>(player.value()->skin(), player.value()));

    }
    if (_stringToOrientation.find(orientation) == _stringToOrientation.end())
        throw std::invalid_argument("Invalid orientation: " + orientation);
    playerOrientation = _stringToOrientation[orientation];
    if (player.value()->orientation() != playerOrientation) {
        // player.value()->pushAnimation();
        player.value()->setOrientation(playerOrientation);
    }
}
