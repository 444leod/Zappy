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

    if (_stringToOrientation.find(orientation) == _stringToOrientation.end())
        throw std::invalid_argument("Invalid orientation: " + orientation);

    playerOrientation = _stringToOrientation[orientation];

    if (gameData->playerExists(playerId))
        throw std::invalid_argument("Player alreasy exist in the game data with this id.");

    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Player position is out of bounds.");

    if (!gameData->teamExists(teamName))
        throw std::invalid_argument("Team does not exist in the game data.");

    std::shared_ptr<gui::Player> newPlayer = std::make_shared<gui::Player>(playerId, Vector2u(x, y), playerOrientation, level, teamName);


    gameData->addPlayer(newPlayer);

    auto tile = gameData->map().at(Vector2u(x, y));
    tile->addEntity(newPlayer);

    auto teamSkin = gameData->teamSkin(teamName);
    newPlayer->setSkin(teamSkin.first);
    newPlayer->setTeamColor(teamSkin.second);

    std::srand(std::time(nullptr));
    newPlayer->setRandomOffset(Vector2f(static_cast<float>(rand() % 30), (rand() % 30)));
}
