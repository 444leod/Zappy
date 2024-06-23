/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#include "Tiles/Map.hpp"

namespace gui {
    std::shared_ptr<Tile> Map::at(Vector2i coordinates) const
    {
        Vector2u pos;

        pos.setX(((coordinates.x() % (int)this->_size.x()) + (int)this->_size.x()) %(int)this->_size.x());
        pos.setY(((coordinates.y() % (int)this->_size.y()) + (int)this->_size.y()) %(int)this->_size.y());
        auto it = this->_tiles.find(pos);
        if (it != this->_tiles.end())
            return it->second;
        else
            throw std::out_of_range("Coordinates out of range");
    }

    std::shared_ptr<Tile> Map::at(Vector2u coordinates) const
    {
        auto it = this->_tiles.find(coordinates);
        if (it != this->_tiles.end())
            return it->second;
        else
            throw std::out_of_range("Coordinates out of range");
    }

    void Map::initializeMap(Vector2u size)
    {
        this->_size = size;
        for (std::uint32_t x = 0; x < size.x(); x++) {
            for (std::uint32_t y = 0; y < size.y(); y++) {
                this->_tiles[{x, y}] = std::make_shared<Tile>();
            }
        }
    }

    void Map::queuePlayerConnexion(std::string fullCommand)
    {
        this->_playerConnexionQueue.push(fullCommand);
    }
}

