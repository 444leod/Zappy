/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Map
*/

#include "Tiles/Map.hpp"

namespace gui {
    TileContent Map::getTileContentByCoordinates(Vector2u coordinates) const
    {
        auto it = this->_mapContent.find(coordinates);
        if (it != this->_mapContent.end())
            return it->second;
        else
            throw std::out_of_range("Coordinates out of range");
    }

    void Map::setTileContentByCoordinates(Vector2u coordinates, TileContent tileContent)
    {
        if (!isValidCoordinates(coordinates))
            throw std::out_of_range("Coordinates out of range");

        this->_mapContent[coordinates] = tileContent;
    }

    void Map::setMapContent(std::map<Vector2u, TileContent> mapContent)
    {
        this->_mapContent.clear();

        for (auto &tile : mapContent) {
            this->_mapContent[tile.first] = tile.second;
        }
    }
}
