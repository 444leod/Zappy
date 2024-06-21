/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pnw
*/

#include "Pnw.hpp"

void gui::Pnw::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    (void)parameters;
    (void)client;
    std::cerr << "Command pnw: can't be staged." << std::endl;
}

void gui::Pnw::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t playerId, level;
    std::uint32_t x, y;
    std::string orientation;
    std::string teamName;
    Orientation playerOrientation;

    iss >> token >> playerId >> x >> y >> orientation >> level >> teamName;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");

    if (gameData->map().size() == Vector2u(0, 0) || gameData->teamNames().size() < 2) {
        gameData->map().queuePlayerConnexion(command);
        return;
    }
    if (_stringToOrientation.find(orientation) == _stringToOrientation.end())
        throw std::invalid_argument("Invalid orientation: " + orientation);
    playerOrientation = _stringToOrientation[orientation];
    if (gameData->playerExists(playerId))
        throw std::invalid_argument("Player alreasy exist in the game data with this id.");
    if (level != 1)
        throw std::invalid_argument("Player must spawn as level 1.");
    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Player position is out of bounds.");
    if (!gameData->teamExists(teamName))
        throw std::invalid_argument("Team does not exist in the game data.");
    std::shared_ptr<gui::Player> newPlayer = std::make_shared<gui::Player>(playerId, Vector2u(x, y), playerOrientation, level, teamName);
    gameData->addPlayer(newPlayer);
    auto tile = gameData->map().at(Vector2u(x, y));
    tile->addEntity(newPlayer);
    newPlayer->setSkin(gameData->teamSkin(teamName).first);
    std::cout << "New player created with id: " << playerId << " at position: " << x << ", " << y << " with orientation: " << orientation << " and level: " << level << " for team: " << teamName << std::endl;

    std::srand(std::time(nullptr));
    newPlayer->setRandomOffset(Vector2f(static_cast<float>(rand() % 30), (rand() % 30)));
}
