/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bct
*/

#include "Bct.hpp"

void gui::Bct::stage(ntw::Client &client, std::string parameters)
{
    client.queueRequest(parameters + "\n");
    client.sendRequests();
}

void gui::Bct::receive(std::string command, GameData &gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t linemate, deraumere, sibur, mendiane, phiras, thystame, food;

    iss >> token >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;

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
