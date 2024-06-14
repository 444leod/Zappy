/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bct
*/

#include "Bct.hpp"

void gui::Bct::stage(ntw::Client &client, std::string parameters)
{
    std::istringstream iss(parameters);
    std::uint32_t x, y;

    iss >> x >> y;

    client.queueRequest("bct " + std::to_string(x) + " " + std::to_string(y));
}

void gui::Bct::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t linemate, deraumere, sibur, mendiane, phiras, thystame, food;

    iss >> token >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (x >= gameData.mapRef().mapSize().x() || y >= gameData.mapRef().mapSize().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    Vector2u coordinates(x, y);
    TileContent tileContent;

    tileContent.rocks().linemate.setQuantity(linemate);
    tileContent.rocks().deraumere.setQuantity(deraumere);
    tileContent.rocks().sibur.setQuantity(sibur);
    tileContent.rocks().mendiane.setQuantity(mendiane);
    tileContent.rocks().phiras.setQuantity(phiras);
    tileContent.rocks().thystame.setQuantity(thystame);
    tileContent.setFood(food);

    gameData.mapRef().setTileContentByCoordinates(coordinates, tileContent);
}
