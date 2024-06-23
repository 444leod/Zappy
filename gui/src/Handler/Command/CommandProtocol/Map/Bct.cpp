/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bct
*/

#include "Bct.hpp"

void gui::Bct::stage(std::shared_ptr<ntw::Client> client, std::string parameters)
{
    if (parameters.empty() || parameters.size() != 2)
        throw std::invalid_argument("Invalid bct arguments");

    client->queueRequest("bct " + parameters);
}

void gui::Bct::receive(std::string command, std::shared_ptr<GameData> gameData)
{
    std::istringstream iss(command);
    std::string token;
    std::uint32_t x, y;
    std::uint32_t linemate, deraumere, sibur, mendiane, phiras, thystame, food;

    iss >> token >> x >> y >> food >> linemate >> deraumere >> sibur >> mendiane >> phiras >> thystame;
    if (iss.fail())
        throw std::invalid_argument("Invalid arguments");
    if (x >= gameData->map().size().x() || y >= gameData->map().size().y())
        throw std::invalid_argument("Invalid tile coordinates, out of map bounds.");
    Vector2u coordinates(x, y);
    auto tile = gameData->map().at(coordinates);

    tile->rocks().linemate.setQuantity(linemate);
    tile->rocks().deraumere.setQuantity(deraumere);
    tile->rocks().sibur.setQuantity(sibur);
    tile->rocks().mendiane.setQuantity(mendiane);
    tile->rocks().phiras.setQuantity(phiras);
    tile->rocks().thystame.setQuantity(thystame);
    tile->setFood(food);

}
